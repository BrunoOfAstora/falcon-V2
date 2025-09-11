#include <stdio.h>
#include "flcn-compare.h"

int flcn_compare_digest(const char *file1, const char *file2)
{
    CmpHash ch = flcn_gen_hash(file1, file2);

    if (flcn_cmp_hashes(&ch) != 0 )
    {
        printf("\033[31mFailed\033[0m: Not the same file\n");
        return 1;
    }
    printf("\033[32mOK\033[0m: File hash match\n");
    return 0;
}