//
// Created by revolver-ocelot on 9/22/25.
//
#include "../inc/re_flcn_save_in_db_operations.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"
#include "../inc/re_flcn_path_builder.h"
#include "../inc/flcn-hashes-handler.h"
#include "../inc/flcn_iterate_dir.h"
#include <linux/limits.h>

#include "../inc/re_flcn_main_handler.h"

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
//    sqlite3_close(db);
    return SQLITE_OK;
}

int flcn_save_in_db_all(sqlite3 *db, const char *directory)
{
    char *f;
    re_save_in_db_create(&db);
    DIR *dir = opendir(directory);
    int f_counter = 1;

    while ((f = flcn_get_all_files_from_dir(dir)) != NULL)
    {
        struct stat st;
        char path[PATH_MAX];

        snprintf(path, sizeof(path), "%s%s", directory, f);

        if (stat(path, &st) != 0)
            continue;

        if (temp_flcn_check_dir(&st) == 0)
            continue;

        printf("Saving %s in DataBase...\n", path);
        re_save_in_db_insert(db, path);
        f_counter++;
    }
    printf("\nFiles Saved %d.\n", f_counter);
    sqlite3_close(db);
    return 0;
}