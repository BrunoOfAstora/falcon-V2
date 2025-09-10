#include "flcn-hashes.h"
//#include "../inc/flcn-hashes.h"

char *flcn_build_hash(const char *file, EVP_MD *md_hash)
{
    FalconHash fh = flcn_open_file(file);

    if (flcn_digest_new(&fh, md_hash))
    {
        void *buf[4096];
        size_t size;
        while ((size = fread(buf, 1, sizeof(buf), fh.usr_file)) > 0)
        {
            flcn_digest_update(&fh, buf, size);
        }
        flcn_digest_final(&fh);
        flcn_clean(&fh, fh.usr_file);

        char *md_digest_result = malloc(2 * fh.hash_len + 1);
        if (md_digest_result)
        {
            size_t i;
            for (i = 0; i < fh.hash_len; i++)
                snprintf(&md_digest_result[i * 2], 32, "%02x", fh.hash_buf[i]);
            md_digest_result[i * 2] = '\0';
            return md_digest_result;
        }
        return NULL;
    }
    return NULL;
}

