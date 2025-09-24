//
// Created by revolver-ocelot on 9/22/25.
//
#include "../inc/re_flcn_save_in_db_operations.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"
#include "../inc/re_flcn_path_builder.h"
#include "../inc/flcn-hashes-handler.h"
#include <linux/limits.h>

int flcn_create_db(sqlite3 **db)
{
    sqlite3_stmt *stmt;

    char db_path[PATH_MAX];
    flcn_build_path_to_db(flcn_get_home_dir(), db_path);
    flcn_dboperations_open_db(db_path, db, FLCN_SQLITE_OPEN_CR | FLCN_SQLITE_OPEN_RW);
    flcn_dboperations_prepare_db(*db, FLCN_SQLITE_CREATE_TABLE, &stmt);
    flcn_dboperations_step_db(stmt);
    flcn_dboperations_finalize_db_stmt(stmt);
    return 0;
}

int flcn_save_name_and_hash_in_db(char *file, sqlite3 *db)
{
    sqlite3_stmt *stmt;

    char db_path[PATH_MAX];
    const char *file_hash = flcn_build_hash(file, EVP_sha256());
    char *realpth = realpath(file, NULL);

    flcn_dboperations_prepare_db(db, FLCN_SQLITE_INSERT_TABLE, &stmt);
    flcn_dboperations_db_bind_text(stmt, 1, realpth);
    flcn_dboperations_db_bind_text(stmt, 2, file_hash);
    flcn_dboperations_step_db(stmt);
    flcn_dboperations_finalize_db_stmt(stmt);

    free(realpth);
    return 0;
}

int flcn_close_db(sqlite3 *db)
{
    flcn_dboperations_close_db(db);
}