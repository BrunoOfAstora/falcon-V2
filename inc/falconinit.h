#ifndef FALCONINIT_H
#define FALCONINIT_H

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define FILE_HASH_BUF_SIZE 4096

typedef struct FalconHashInit
{

	FILE *file_usr_stream;
	size_t buf_hash_size;
	size_t bytes_read;

	uint8_t file_hash_buf_s[FILE_HASH_BUF_SIZE];
	unsigned char md_hash_buf[EVP_MAX_MD_SIZE];
	unsigned int hash_md_leng;	

	char *hex_hash_result;
	
}flcn_init;


char *flcn_md5_hash(const char *usr_in);

char *flcn_256_hash(const char *usr_in);

char *flcn_384_hash(const char *usr_in);

char *flcn_512_hash(const char *usr_in);

#endif
