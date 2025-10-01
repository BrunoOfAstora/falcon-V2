//
// Created by revolver-ocelot on 9/30/25.
//

#include "re_flcn_compare_handler.h"

#include <stddef.h>
#include <string.h>
#include <sys/stat.h>

#include "../inc/re_flcn_main_handler.h"
#include "../inc/re_flcn_path_builder.h"

int flcn_cmp_save_info(const char *file1, const char *file2, Flcn_cmp_hashes *f_info)
{
    if (file1 == NULL || file2 == NULL)
        return -1;

    struct stat st1, st2;
    if (stat(file1, &st1) != 0 || stat(file2, &st2) != 0)
        return -2;

    if (!S_ISREG(st1.st_mode) || !S_ISREG(st2.st_mode))
        return -3;

    memcpy(f_info->file1_name, flcn_get_real_path(file1), strlen(file1));
    memcpy(f_info->file2_name, flcn_get_real_path(file2), strlen(file1));

    memcpy(f_info->hash_f1, flcn_calculate_hash(file1, EVP_sha256()), 32);
    memcpy(f_info->hash_f2, flcn_calculate_hash(file2, EVP_sha256()), 32);
    return 0;
}

int flcn_cmp_hashes(Flcn_cmp_hashes *f_info)
{
    if (f_info == NULL)
        return -1;

    if (strlen(f_info->hash_f1) != strlen(f_info->hash_f2))
        return -2;

    return CRYPTO_memcmp(f_info->hash_f1, f_info->hash_f2, 32);
}