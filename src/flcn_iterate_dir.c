//
// Created by revolver-ocelot on 10/8/25.
//

#include "flcn_iterate_dir.h"

#include <dirent.h>
#include <stddef.h>

char *flcn_get_all_files_from_dir(DIR *dir)
{
    if (!dir)
        return NULL;

    struct dirent *d = readdir(dir);
    if (d == NULL)
        return NULL;
    return d->d_name;
}