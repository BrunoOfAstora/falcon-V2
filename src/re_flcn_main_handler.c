//
// Created by revolver-ocelot on 9/22/25.
//

#include "../inc/re_flcn_main_handler.h"
#include "../inc/re_flcn_main.h"
#include "../inc/flcn-hashes-handler.h"
#include "../inc/re_flcn_sqlite_operations_handler.h"
#include "../inc/re_flcn_verify.h"

/*void flcn_print_usage_msg(char *name)
{
    printf("a");
}
*/
void flcn_print_func_usage_msg()
{
    printf("Error: This option requires a file as argument, but got '%s' as argument instead\n", optarg);
}

//Hashes
char * flcn_calculate_hash(const char *mode,const EVP_MD *md_hash)
{
    printf("Calculating hash..."); FF;
    if (mode[0] == '-')
    {
        flcn_print_func_usage_msg();
        return NULL;
    }
    char *hash = flcn_build_hash(mode, md_hash);
    if (hash == NULL )
    {
        printf("The file dont exist; can't be opened, or an error occurred during hash calculation.\n");
        return NULL;
    }
    printf("\033[32mDONE!\033[0m\n");

    return hash;
}

int flcn_save_data_in_db(char *file)
{
    sqlite3 *db;
    if ((re_save_in_db_create(&db)) != SQLITE_OK) return -1;
    if ((re_save_in_db_insert(db, file)) != SQLITE_OK) return -2;
    sqlite3_close(db);
    return 0;
}

int flcn_save_all_data_in_db(char *dir)
{
    sqlite3 *db;
    flcn_save_in_db_all(db, dir);
    return 0;
}

int flcn_check_valid_file(const char *file, struct stat *st)
{
    if (stat(file, st) != 0)
        return 1;
    return 0;
}

int flcn_check_reg_file(struct stat *st)
{
    if (S_ISREG(st->st_mode))
        return 0;
    return 1;
}

int temp_flcn_check_dir(struct stat *st)
{
    if (S_ISDIR(st->st_mode))
        return 0;
    return 1;
}