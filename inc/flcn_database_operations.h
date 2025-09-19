#ifndef FALCON_V2_FLCN_VERIFY_H
#define FALCON_V2_FLCN_VERIFY_H

#include <sqlite3.h>
#include <openssl/crypto.h>

#define FLCN_SQL_REQUEST "SELECT f_name, f_hash FROM flcn_hashes WHERE f_name = ?"

typedef enum
{
    FLCN_DB_ROW,
    FLCN_DB_DONE,
    FLCN_DB_ERROR
};

typedef struct CmpHandler
{
    char *file_hash;
    char *file_name;
}CmpHandler;
char *flcn_get_file_path(const char *file_name);

int flcn_dboperations_init_db(sqlite3 **db, const char *db_path);

int flcn_dboperations_prepare_db(sqlite3 *db, const char *request, sqlite3_stmt **stmt);

int flcn_dboperations_db_bind_text(sqlite3_stmt *stmt, const char *file_name);

int flcn_dboperations_step_db(sqlite3_stmt *stmt);

void flcn_dboperations_finalize_db_stmt(sqlite3_stmt *stmt);

void flcn_dboperations_close_db(sqlite3 *db);

char *flcn_dboperations_column_strdup(sqlite3_stmt *stmt, int column);

int flcn_crypto_cmp(char *str1, char *str2, size_t len);

int flcn_verify_digest(CmpHandler *cmp_handler, sqlite3 *db, sqlite3_stmt *stmt, const char *db_path,char *file_name);

#endif //FALCON_V2_FLCN_VERIFY_H