//
// Created by revolver-ocelot on 10/2/25.
//
#include "re_flcn_verify.h"
#include "../inc/re_flcn_path_builder.h"
#include "../inc/flcn-hashes-handler.h"
#include "../inc/re_flcn_main_handler.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"

#include <sqlite3.h>
#include <string.h>
#include <sys/stat.h>

int flcn_verify(const char *file_name)
{
    if (file_name == NULL)
        return -1;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    struct stat *st = malloc(sizeof(struct stat));

    const char *full_file_path = flcn_get_real_path(file_name);
    const char *file_hash = flcn_build_hash(file_name, EVP_sha256());

    printf("file_name param: '%s'\n", file_name);
    printf("full_file_path -> '%s'\n", full_file_path);
    printf("file_hash -> '%s'\n", file_hash);

    if (flcn_check_valid_file(file_name, st) != 0)
        return -1;
    if (flcn_check_reg_file(st) != 0)
        return -2;

    char db_path[PATH_MAX];
    flcn_build_path_to_db(flcn_get_home_dir(), db_path);
    printf("DB path -> '%s'\n", db_path);

    flcn_dboperations_open_db(db_path, &db, FLCN_SQLITE_OPEN_RW);
    flcn_dboperations_prepare_db(db, FLCN_SQL_REQUEST, &stmt);
    flcn_dboperations_db_bind_text(stmt, 1, full_file_path);
    int step = flcn_dboperations_step_db(stmt);
    printf("Step: %d\n", step);

    if (step == SQLITE_ROW)
    {
        int file_status = 0;
        const char *dup_db_file_name = flcn_dboperations_column_strdup(stmt, 0);
        const char *dup_db_file_hash = flcn_dboperations_column_strdup(stmt, 1);

        if (CRYPTO_memcmp(dup_db_file_name, full_file_path, strlen(dup_db_file_name)) != 0)
            file_status += 1;
        if (CRYPTO_memcmp(dup_db_file_hash, file_hash, strlen(dup_db_file_hash)) != 0)
            file_status += 2;

        flcn_dboperations_finalize_db_stmt(stmt);
        flcn_dboperations_close_db(db);
        printf("Return: %d", file_status);
        return file_status;
    }
    return -3;
}