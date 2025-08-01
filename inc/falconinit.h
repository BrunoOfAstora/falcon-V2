//		falconinit.h

#ifndef FALCONINIT_H
#define FALCONINIT_H

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <ftw.h>
#include <getopt.h>
#include "uthash.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>

#define FILE_HASH_BUF_SIZE 4096
#define FILE_NAME_BUFFER_SIZE_ 128
#define FILE_HASH_BUFFER_SIZE_ 256
#define FULL_PATH_SIZE_ 512


//		*******************
//		**General Purpose**
//		*******************

char *flcn_GetHomeDir();

size_t flcn_SetHashDirInHome(char *out_path, size_t size);

size_t flcn_CreateDbFile(char *out_path, size_t size);

bool sec_strcmp(const char *str1, const char *str2, size_t size);

bool sec_memcmp(const void *blk1, const void *blk2, const size_t size);

typedef struct FalconHashInit
{

	FILE *file_usr_stream; //---------------------------->Used to open the user file
	
	size_t buf_hash_size;//------------------------------>Store the size of the hash buffer

	size_t bytes_read;//--------------------------------->Quantity of bytes readed from the stream

	uint8_t file_hash_buf_s[FILE_HASH_BUF_SIZE];//------->Size of buffer to store the hash (64) -> *Openssl Documentation
	
	unsigned char md_hash_buf[(16 + 20)];//-------->Actual buffer that contains chuncks of hash
	
	unsigned int hash_md_leng;//------------------------->Defines the lenght of hash to write on	

	char *hex_hash_result;//----------------------------->Stores the result of given hash
	
}flcn_init;

typedef struct FalconSaveInit
{
	DIR *curr_dir;
	
	FILE *file_usr_stream;

	char hash_folder_path[PATH_MAX];
	
	char full_db_path[PATH_MAX];

	char *f_all_name;

	char *f_hash;

}flcn_save;

extern flcn_save *flcn_save_init;

void _save_init();
void _save_deinit(void);

//		******************
//		**HASH Functions**
//		******************

//Returns the MD5 hash of the file passed
char *flcn_md5_hash(const char *usr_in);


//Returns the SHA256 hash of the file passed
char *flcn_256_hash(const char *usr_in);


//Returns the SHA384 hash of the file passed
char *flcn_384_hash(const char *usr_in);


//Returns the SHA512 hash of the file passed
char *flcn_512_hash(const char *usr_in);



//		******************
//		**Save Functions**
//		******************

//Saves the file name and fiel hash in a DB (SQLite3)
int save_in_db(char *f_name);

int save_in_db_all(const char *start_path);

int save_in_db_callback(const char *f_path, const struct stat *st, int flag, struct FTW *ftwbuf);


//		********************
//		**Verify Functions**
//		********************

int flcn_verify(char *f_name);

int flcn_verify_all(const char *start_path);

int verify_callback(const char *f_path, const struct stat *st, int flag, struct FTW *ftwbuf);


//		*******************
//		*remove duplicates*
//		*******************

int rmdup();

#endif
