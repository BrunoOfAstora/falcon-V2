#include <openssl/evp.h>

#ifndef FALCON_V2_FLCN_HASHES_H
#define FALCON_V2_FLCN_HASHES_H

typedef struct FalconHash
{
    FILE *usr_file;
    EVP_MD_CTX *ctx;
    unsigned char hash_buf[(16+20)];
    unsigned int hash_len;

} FalconHash;

FalconHash flcn_open_file(const char *user_input_file);

int flcn_digest_new(FalconHash *fh, const EVP_MD *md_hash);

int flcn_digest_update(FalconHash *fh, const void *buf, size_t size);

int flcn_digest_final(FalconHash *fh);

int flcn_clean(FalconHash *fh, FILE *file);

char *flcn_build_hash(const char *file, EVP_MD *md_hash);

#endif //FALCON_V2_FLCN_HASHES_H