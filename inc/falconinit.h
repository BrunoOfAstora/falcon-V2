#ifndef FALCONINIT_H
#define FALCONINIT_H

#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define FILE_HASH_BUF_SIZE 4096

typedef struct FalconHashInit
{

	FILE *file_usr_stream; //---------------------------->Used to open the user file
	
	size_t buf_hash_size;//------------------------------>Store the size of the hash buffer

	size_t bytes_read;//--------------------------------->Quantity of bytes readed from the stream

	uint8_t file_hash_buf_s[FILE_HASH_BUF_SIZE];//------->Size of buffer to store the hash (64) -> *Openssl Documentation
	
	unsigned char md_hash_buf[EVP_MAX_MD_SIZE];//-------->Actual buffer that contains chuncks of hash
	
	unsigned int hash_md_leng;//------------------------->Defines the lenght of hash to write on	

	char *hex_hash_result;//----------------------------->Stores the result of given hash
	
}flcn_init;

//Returns the MD5 hash of the file passed
char *flcn_md5_hash(const char *usr_in);


//Returns the SHA256 hash of the file passed
char *flcn_256_hash(const char *usr_in);


//Returns the SHA384 hash of the file passed
char *flcn_384_hash(const char *usr_in);


//Returns the SHA512 hash of the file passed
char *flcn_512_hash(const char *usr_in);

#endif
