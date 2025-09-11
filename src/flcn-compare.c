#include "flcn-compare.h"
#include "flcn-hashes.h"
#include <openssl/crypto.h>

CmpHash flcn_gen_hash(const char *file1, const char *file2)
{
	CmpHash ch = {0};

	ch.file1_hash = flcn_build_hash(file1, EVP_sha384());
	ch.file2_hash = flcn_build_hash(file2, EVP_sha384());

	return ch;
}

int flcn_cmp_hashes(CmpHash *ch)
{
	return CRYPTO_memcmp(ch->file1_hash, ch->file2_hash, 48);
}