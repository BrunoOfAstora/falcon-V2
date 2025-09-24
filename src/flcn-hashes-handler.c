#include "falconinit.h"
#include "flcn-hashes-handler.h"

FalconHash flcn_open_file(const char *user_input_file)
{
	FalconHash fh = {0};

	fh.usr_file = fopen(user_input_file, "rb");
	if (fh.usr_file == NULL)
	{
		perror("fopen error while calculating hash");
	}
	return fh;
}

int flcn_digest_new(FalconHash *fh, const EVP_MD *md_hash)
{
	fh->ctx = EVP_MD_CTX_new();
	if (!fh->ctx) return 0;

	return EVP_DigestInit_ex(fh->ctx, md_hash,NULL);
}

int flcn_digest_update(FalconHash *fh, const void *buf, size_t size)
{
	if (!fh->ctx) return 0;
	return EVP_DigestUpdate(fh->ctx, buf, size);
}

int flcn_digest_final(FalconHash *fh)
{
	return EVP_DigestFinal_ex(fh->ctx, fh->hash_buf, &fh->hash_len);
}

int flcn_clean(FalconHash *fh, FILE *file)
{
	if (fh->ctx)
		EVP_MD_CTX_free(fh->ctx);

	if (file)
		fclose(file);

	return 0;
}