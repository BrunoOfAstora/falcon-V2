#ifndef FALCON_V2_FLCN_COMPARE_H
#define FALCON_V2_FLCN_COMPARE_H

typedef struct CmpHash
{
    char *file1_hash;
    char *file2_hash;

}CmpHash;

CmpHash flcn_gen_hash(const char *file1, const char *file2);

int flcn_cmp_hashes(CmpHash *ch);

int flcn_compare_digest(const char *file1, const char *file2);


#endif //FALCON_V2_FLCN_COMPARE_H