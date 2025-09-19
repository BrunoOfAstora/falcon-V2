#ifndef FALCON_V2_FLCN_INIT_H
#define FALCON_V2_FLCN_INIT_H

#include <linux/limits.h>

typedef struct DbPath
{
    char db_path_buf[PATH_MAX];
}DbPath;

char *flcn_get_home_dir();

void flcn_build_db_path(DbPath *dbpath, size_t size, char *home_path);

void *flcn_build_file_in_db_path(DbPath *db_path, size_t size, const char *filename);

#endif //FALCON_V2_FLCN_INIT_H