//
// Created by revolver-ocelot on 9/30/25.
//

#include "re_flcn_compare_handler.h"

#include <stddef.h>
#include <string.h>
#include <sys/stat.h>

#include "../inc/re_flcn_main_handler.h"
#include "../inc/re_flcn_path_builder.h"

int flcn_cmp_hashes(const char *file1, const char *file2)
{
    if (file1 == NULL || file2 == NULL)
        return -1;

    const char *file1_hash = flcn_calculate_hash(file1, EVP_sha256());
    const char *file2_hash = flcn_calculate_hash(file2, EVP_sha256());

    if ((strlen(file1_hash)) != (strlen(file2_hash)))
        return 2;

    return CRYPTO_memcmp(file1_hash, file2_hash, 32);
}