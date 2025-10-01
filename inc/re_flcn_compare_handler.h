//
// Created by revolver-ocelot on 9/30/25.
//

#ifndef FALCON_V2_RE_FLCN_COMPARE_HANDLER_H
#define FALCON_V2_RE_FLCN_COMPARE_HANDLER_H
#include <linux/limits.h>

typedef struct Flcn_cmp_hashes
{
    unsigned char hash_f1[32];
    unsigned char hash_f2[32];

    unsigned char file1_name[PATH_MAX];
    unsigned char file2_name[PATH_MAX];

}Flcn_cmp_hashes;

int flcn_cmp_save_info(const char *file1, const char *file2, Flcn_cmp_hashes *f_info);

int flcn_cmp_hashes(Flcn_cmp_hashes *f_info);

#endif //FALCON_V2_RE_FLCN_COMPARE_HANDLER_H