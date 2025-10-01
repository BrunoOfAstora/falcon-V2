//
// Created by revolver-ocelot on 9/30/25.
//

#include "../inc/re_flcn_compare.h"
#include "../inc/re_flcn_compare_handler.h"

int flcn_cmp(const char *file1, const char *file2)
{
    Flcn_cmp_hashes *flcn_info = malloc(sizeof(Flcn_cmp_hashes));
    if (!flcn_info)
        return -1;

    flcn_cmp_save_info(file1, file2, flcn_info);
    return flcn_cmp_hashes(flcn_info);
}