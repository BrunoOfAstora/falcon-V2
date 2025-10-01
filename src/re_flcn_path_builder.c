//
// Created by revolver-ocelot on 9/22/25.
//
#include "../inc/re_flcn_path_builder.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

char * flcn_get_real_path(const char *file_name)
{
    char * realpth = realpath(file_name,NULL);
    if (realpth == NULL)
        return NULL;
    return realpth;
}

char * flcn_get_home_dir()
{
    return getenv("HOME");
}

char * flcn_build_path_to_db(char *home_dir, char *database_dest)//
{
    if (home_dir == NULL)
        home_dir = "/tmp";

    snprintf(database_dest, PATH_MAX, "%s/%s/", home_dir, ".falcon_hashes");
    mkdir(database_dest, 0700);

    size_t len = strnlen(database_dest, PATH_MAX);
    snprintf(database_dest + len, PATH_MAX - len, "%s", ".flcn_hashes");

    FILE *f = fopen(database_dest, "a+");
    fclose(f);

    return database_dest;
}
