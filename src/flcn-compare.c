#include "falconinit.h"
#include <openssl/crypto.h>

int flcn_cmp_hash(const char *f1, const char *f2)
{

	if(f1 == NULL || f2 == NULL)
		return -1;

	char *f1_hash = flcn_384_hash(f1);

	char *f2_hash = flcn_384_hash(f2);

	if(f1_hash == NULL || f2_hash == NULL)
	{
		printf("Need to specify the files\n");
		return -2;
	}

	int cmp = CRYPTO_memcmp(f1_hash, f2_hash, 48);
	if(cmp != 0)
	{
		printf("\033[31mFailed\033[0m: Not the same file\n");
		return 1;
	}

	printf("\033[32mOK\033[0m: File hash match\n");

	return 0;
	
}
