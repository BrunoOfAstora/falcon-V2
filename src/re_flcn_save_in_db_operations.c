//
// Created by revolver-ocelot on 9/22/25.
//
#include "../inc/re_flcn_save_in_db_operations.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"
#include "../inc/re_flcn_path_builder.h"
#include "../inc/flcn-hashes-handler.h"
#include <linux/limits.h>

int re_save_in_db_create(sqlite3 **db)
{
    if (db == NULL)
        return -1;

    sqlite3_stmt *stmt;
    char flcn_db_dest[PATH_MAX];

    if ((flcn_dboperations_open_db(flcn_build_path_to_db(flcn_get_home_dir(), flcn_db_dest), db, FLCN_SQLITE_OPEN_CR | FLCN_SQLITE_OPEN_RW)) != SQLITE_OK) return -1;
    if ((flcn_dboperations_prepare_db(*db, FLCN_SQLITE_CREATE_TABLE, &stmt)) != SQLITE_OK)return -2;
    if ((flcn_dboperations_step_db(stmt)) != SQLITE_DONE) return -3;
    if ((flcn_dboperations_finalize_db_stmt(stmt)) != SQLITE_OK) return -4;

    return SQLITE_OK;
}

int re_save_in_db_insert(sqlite3 *db, char *file)
{
    if (db == NULL || file == NULL)
        return -1;

    struct stat st;

    if (stat(file, &st) != 0)
        return -2;

    if (!S_ISREG(st.st_mode))
        return -3;

    sqlite3_stmt *stmt;
    const char *file_hash = flcn_build_hash(file, EVP_sha256());
    const char *abs_file = realpath(file, NULL);
    if (abs_file == NULL || file_hash == NULL)
        return -10;

    if ((flcn_dboperations_prepare_db(db, FLCN_SQLITE_INSERT_TABLE, &stmt)) != SQLITE_OK) return -2;
    if ((flcn_dboperations_db_bind_text(stmt, 1, abs_file)) != SQLITE_OK) return -3;
    if ((flcn_dboperations_db_bind_text(stmt, 2, file_hash)) != SQLITE_OK) return -3;
    if ((flcn_dboperations_step_db(stmt)) != SQLITE_DONE) return -5;
    if ((flcn_dboperations_finalize_db_stmt(stmt)) != SQLITE_OK) return -6;
    sqlite3_close(db);

    return SQLITE_OK;
}