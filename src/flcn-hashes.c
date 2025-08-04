#include "falconinit.h"
#include <openssl/evp.h>


//			*********
//			***MD5***
//			*********
char *flcn_md5_hash( const char *usr_in )
{
	struct FalconHashInit *flcn_init = malloc(sizeof(struct FalconHashInit));

	char *ret_val = NULL;

	if(flcn_init == NULL || usr_in == NULL)
	{
		printf("Need to specify the file and initializer\n");
		return NULL;
	}

	flcn_init->file_usr_stream = fopen(usr_in, "rb");
	if(!flcn_init->file_usr_stream)
	{
		printf("Error while opening file\n");
		goto end_func;
	}


	EVP_MD_CTX *md5_ctx = EVP_MD_CTX_new();
	if(md5_ctx == NULL)
	{
		perror("Error while creating EVP_MD_CTX_new\n");
		goto end_func;
	}


	int evp_md5_init = EVP_DigestInit_ex(md5_ctx, EVP_md5(), NULL);
	if(!evp_md5_init)
	{
		perror("Error while initializing MD5 hash Algorithim\n");
		goto end_func;
	}

	
	while((flcn_init->bytes_read = fread(flcn_init->md_hash_buf, 1, sizeof(flcn_init->md_hash_buf), flcn_init->file_usr_stream)) > 0)
	{
		int evp_md5_update = EVP_DigestUpdate(md5_ctx, flcn_init->md_hash_buf, flcn_init->bytes_read);
		if(!evp_md5_update)
		{
			perror("Error While Updating MD5 Hash\n");
			goto end_func;
		}

	}

	int evp_md5_digest_final = EVP_DigestFinal_ex(md5_ctx, flcn_init->md_hash_buf, &flcn_init->hash_md_leng);
	if(!evp_md5_digest_final)
	{
		perror("Error Finishing MD5 Update\n");
		goto end_func;
	}

	EVP_MD_CTX_free(md5_ctx);
	fclose(flcn_init->file_usr_stream);

	flcn_init->hex_hash_result = malloc( 2 * flcn_init->hash_md_leng + 1 );
	if(!flcn_init->hex_hash_result)
	{
		perror("Error: Failed To Allocate Memory For The Hash Result\n");
		goto end_func;
	}
	
	size_t i;
	for(i = 0; i < flcn_init->hash_md_leng; i++)
		snprintf(&flcn_init->hex_hash_result[i * 2], 32,"%02x", flcn_init->md_hash_buf[i]);

	flcn_init->hex_hash_result[i * 2] = '\0';
			
	ret_val = flcn_init->hex_hash_result;

	return ret_val;

end_func:

	if(flcn_init->file_usr_stream)
		fclose(flcn_init->file_usr_stream);

	if(flcn_init->hex_hash_result)
		free(flcn_init->hex_hash_result);

	if(flcn_init)
		free(flcn_init);

	return ret_val;

}


//				**********
//				**SHA256**
//				**********
char *flcn_256_hash( const char *usr_in )
{
	struct FalconHashInit *flcn_init = malloc(sizeof(struct FalconHashInit));

	char *ret_val = NULL;

	if(flcn_init == NULL || usr_in == NULL)
	{
		printf("Need to specify the file and initializer\\n");
		return NULL;
	}

	flcn_init->file_usr_stream = fopen(usr_in, "rb");
	if(!flcn_init->file_usr_stream)
	{
		printf("Error while opening file\n");
		goto end_func;
	}


	EVP_MD_CTX *s256_ctx = EVP_MD_CTX_new();
	if(s256_ctx == NULL)
	{
		perror("Error while creating EVP_MD_CTX_new\n");
		goto end_func;
	}


	int evp_s256_init = EVP_DigestInit_ex(s256_ctx, EVP_sha256(), NULL);
	if(!evp_s256_init)
	{
		perror("Error while initializing SHA256 hash Algorithim\n");
		goto end_func;
	}

	
	while((flcn_init->bytes_read = fread(flcn_init->md_hash_buf, 1, sizeof(flcn_init->md_hash_buf), flcn_init->file_usr_stream)) > 0)
	{
		int evp_s256_update = EVP_DigestUpdate(s256_ctx, flcn_init->md_hash_buf, flcn_init->bytes_read);
		if(!evp_s256_update)
		{
			perror("Error While Updating SHA256 Hash\n");
			goto end_func;
		}

	}

	int evp_s256_digest_final = EVP_DigestFinal_ex(s256_ctx, flcn_init->md_hash_buf, &flcn_init->hash_md_leng);
	if(!evp_s256_digest_final)
	{
		perror("Error Finishing SHA256 Update\n");
		goto end_func;
	}

	EVP_MD_CTX_free(s256_ctx);
	fclose(flcn_init->file_usr_stream);

	flcn_init->hex_hash_result = malloc( 2 * flcn_init->hash_md_leng + 1 );
	if(!flcn_init->hex_hash_result)
	{
		perror("Error: Failed To Allocate Memory For The Hash Result\n");
		goto end_func;
	}
	
	size_t i;
	for(i = 0; i < flcn_init->hash_md_leng; i++)
		snprintf(&flcn_init->hex_hash_result[i * 2], 32,"%02x", flcn_init->md_hash_buf[i]);

	flcn_init->hex_hash_result[i * 2] = '\0';
			
	ret_val = flcn_init->hex_hash_result;
	return ret_val;

end_func:
	
	if(flcn_init->file_usr_stream)
		fclose(flcn_init->file_usr_stream);

	if(flcn_init->hex_hash_result)
		free(flcn_init->hex_hash_result);

	if(flcn_init)
		free(flcn_init);

	return ret_val;

}



//				**********
//				**SHA384**	
//				**********

char *flcn_384_hash(const char *usr_in)
{
    struct FalconHashInit *flcn_init = malloc(sizeof(*flcn_init));
    if (!flcn_init || !usr_in) 
	{
        fprintf(stderr, "Need to specify the file and initializer\n");
        free(flcn_init);
        return NULL;
    }

    FILE *f = fopen(usr_in, "rb");
    if (!f) 
	{
        perror("Error opening file");
        free(flcn_init);
        return NULL;
    }
    flcn_init->file_usr_stream = f;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) 
	{
        perror("Error creating EVP_MD_CTX");
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    if (!EVP_DigestInit_ex(ctx, EVP_sha384(), NULL)) 
	{
        perror("EVP_DigestInit_ex");
        EVP_MD_CTX_free(ctx);
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    while ((flcn_init->bytes_read = fread(flcn_init->md_hash_buf, 1, sizeof(flcn_init->md_hash_buf), f)) > 0) 
	{
        if (!EVP_DigestUpdate(ctx, flcn_init->md_hash_buf, flcn_init->bytes_read)) 
		{
            perror("EVP_DigestUpdate");
            EVP_MD_CTX_free(ctx);
            fclose(f);
            free(flcn_init);
            return NULL;
        }
    }

    if (!EVP_DigestFinal_ex(ctx, flcn_init->md_hash_buf, &flcn_init->hash_md_leng)) 
	{
        perror("EVP_DigestFinal_ex");
        EVP_MD_CTX_free(ctx);
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    EVP_MD_CTX_free(ctx);
    fclose(f);

    char *hex_hash = malloc(2 * flcn_init->hash_md_leng + 1);
    if (!hex_hash) {
        perror("malloc hex_hash");
        free(flcn_init);
        return NULL;
    }

    for (size_t i = 0; i < flcn_init->hash_md_leng; i++)
        sprintf(&hex_hash[i * 2], "%02x", flcn_init->md_hash_buf[i]);
    hex_hash[flcn_init->hash_md_leng * 2] = '\0';

    free(flcn_init);
    return hex_hash; 
}


//				**********
//				**SHA512**	
/*				**********
char *flcn_512_hash(const char *usr_in)
{
    struct FalconHashInit *flcn_init = malloc(sizeof(*flcn_init));
    if (!flcn_init || !usr_in) 
	{
        fprintf(stderr, "Need to specify the file and initializer\n");
        free(flcn_init);
        return NULL;
    }

    FILE *f = fopen(usr_in, "rb");
    if (!f) 
	{
        perror("Error opening file");
        free(flcn_init);
        return NULL;
    }
    flcn_init->file_usr_stream = f;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) 
	{
        perror("Error while creating EVP_MD_CTX");
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    if (!EVP_DigestInit_ex(ctx, EVP_sha512(), NULL)) 
	{
        perror("error in: EVP_DigestInit_ex");
        EVP_MD_CTX_free(ctx);
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    while ((flcn_init->bytes_read = fread(flcn_init->md_hash_buf, 1, sizeof(flcn_init->md_hash_buf), f)) > 0) 
	{
        if (!EVP_DigestUpdate(ctx, flcn_init->md_hash_buf, flcn_init->bytes_read)) 
		{
            perror("error in: EVP_DigestUpdate");
            EVP_MD_CTX_free(ctx);
            fclose(f);
            free(flcn_init);
            return NULL;
        }
    }

    if (!EVP_DigestFinal_ex(ctx, flcn_init->md_hash_buf, &flcn_init->hash_md_leng)) 
	{
        perror("error in: EVP_DigestFinal_ex");
        EVP_MD_CTX_free(ctx);
        fclose(f);
        free(flcn_init);
        return NULL;
    }

    EVP_MD_CTX_free(ctx);
    fclose(f);

    char *hex_hash = malloc(2 * flcn_init->hash_md_leng + 1);
    if (!hex_hash) {
        perror("malloc hex_hash");
        free(flcn_init);
        return NULL;
    }

    for (size_t i = 0; i < flcn_init->hash_md_leng; i++)
        sprintf(&hex_hash[i * 2], "%02x", flcn_init->md_hash_buf[i]);
    hex_hash[flcn_init->hash_md_leng * 2] = '\0';

    free(flcn_init);
    return hex_hash; 
}

*/


