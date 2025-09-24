#include <string.h>
#include "flcn-hashes-handler.h"
#include "flcn-compare.h"
#include "flcn_verify.h"
#include "../inc/flcn-hashes-handler.h"

int flcn_verify_digest(CmpHandler *cmp_handler, sqlite3 *db, sqlite3_stmt *stmt, const char *db_path,char *file_name)
{
    char * fn = flcn_get_file_path(file_name);
    if (fn == NULL)
        return -1;

    unsigned int file_flag = 0;

    CmpHandler *ch;

    cmp_handler->file_name = fn;

    flcn_dboperations_open_db(db_path, &db, FLCN_SQLITE_OPEN_RW);
    flcn_dboperations_prepare_db(db, FLCN_SQL_REQUEST, &stmt);

    const char *file_hash = flcn_build_hash(file_name, EVP_sha256());

    flcn_dboperations_db_bind_text(stmt, 1,file_name);
    int step = flcn_dboperations_step_db(stmt);
    if (step == FLCN_DB_ROW)
    {
        ch->file_name = flcn_dboperations_column_strdup(stmt, 0);
        ch->file_hash = flcn_dboperations_column_strdup(stmt, 1);

        if (flcn_crypto_cmp(ch->file_name, file_name, strlen(ch->file_name)) != 0)
            file_flag += 1;

        if (flcn_crypto_cmp(ch->file_hash, file_hash, 32 ) != 0)
            file_flag += 2;
    }
    if (stmt) flcn_dboperations_finalize_db_stmt(stmt);
    if (db)   flcn_dboperations_close_db(db);
    return file_flag;
}