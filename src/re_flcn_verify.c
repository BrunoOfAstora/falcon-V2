//
// Created by revolver-ocelot on 10/2/25.
//
#include "re_flcn_verify.h"

#include <dirent.h>

#include "../inc/re_flcn_path_builder.h"
#include "../inc/flcn-hashes-handler.h"
#include "../inc/re_flcn_main_handler.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"

#include <sqlite3.h>
#include <string.h>
#include <sys/stat.h>

#include "../inc/flcn_iterate_dir.h"
#include "../inc/re_flcn_save_in_db_operations.h"

int flcn_verify(const char *file_name)
{
    if (file_name == NULL)
        return -1;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    struct stat *st = malloc(sizeof(struct stat));

    const char *full_file_path = flcn_get_real_path(file_name);
    const char *file_hash = flcn_build_hash(file_name, EVP_sha256());

    printf("File Actual Path -> '%s'\n", full_file_path);

    if (flcn_check_valid_file(file_name, st) != 0)
    {
        free(st);
        return -1;
    }
    if (flcn_check_reg_file(st) != 0)
    {
        free(st);
        return -2;
    }

    char db_path[PATH_MAX];
    flcn_build_path_to_db(flcn_get_home_dir(), db_path);
    printf("file_hash -> '%s'\n", file_hash);

    flcn_dboperations_open_db(db_path, &db, FLCN_SQLITE_OPEN_RW);
    flcn_dboperations_prepare_db(db, FLCN_SQL_REQUEST, &stmt);
    flcn_dboperations_db_bind_text(stmt, 1, full_file_path);
    int step = flcn_dboperations_step_db(stmt);

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
        if (file_status == 0)
        {
            printf("File Status:\033[32mOK!\033[0m\n -> %d\n", file_status);
            free(st);
        }
        if (file_status == 1)
        {
            printf("File Status:\033[33mWARNING!\033[0m\nThe file have the same Hash, but with a different name -> %d\n", file_status);
            free(st);
        }
        if (file_status == 2 || file_status == 3)
        {
            printf("File Status:\033[31mFAILED!\033[0m\nnThe file was modified, is corrupted, or it's a different file -> %d\n", file_status);
            free(st);
        }
        return file_status;
    }
    free(st);
    return -3;
}

bool flcn_verify_all_files(const char *directory)
{
    char *f;
    DIR *dir = opendir(directory);

    int files_status_ok = 0;
    int files_status_failed = 0;

    while ((f = flcn_get_all_files_from_dir(dir)) != NULL)
    {
        struct stat st;
        char path[PATH_MAX];

        snprintf(path, sizeof(path), "%s%s", directory, f);

        if (stat(path, &st) != 0)
            continue;

        if (temp_flcn_check_dir(&st) == 0)
            continue;

        printf("\n\n");
        printf("Verifying %s...\n", path);
        if (flcn_verify(path) == 0)
            files_status_ok++;
        else
            files_status_failed++;
    }
    printf("\n------------------------------\n");
    printf("Files 'OK': %d\nFiles 'Failed': %d\n", files_status_ok, files_status_failed);
    return true;
}