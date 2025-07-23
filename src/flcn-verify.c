#include "falconinit.h"
#include <sqlite3.h>
#include <ftw.h>

typedef struct Compare_att
{
	char *hash;
	char *f_name;

}cmp_info;

int verify_callback(const char *f_path, const struct stat *st, int flag, struct FTW *ftwbuf)
{
	(void)st;    
    (void)ftwbuf; 	

	if(flag == FTW_F)
	{
		flcn_verify((char *)f_path);
	}

	return 0;
}




int flcn_verify_all(const char *start_path)
{
	struct stat st;
	
	if(stat(start_path, &st) == -1)
	{
		perror("Start Failed:");
		return 1;
	}

	if(S_ISDIR(st.st_mode))
		return nftw(start_path, verify_callback, 12, FTW_PHYS);

	else if (S_ISREG(st.st_mode))
		return flcn_verify((char *)start_path);

	else
	{
		printf("Unsupported file type\n");
		return 1;
	}
}




int flcn_verify(char *f_name)
{

	flcn_save *flcn_save = malloc(sizeof *flcn_save);	
	sqlite3 *db;
	sqlite3_stmt *stmt;

	bool f_name_flag = false;
	bool f_hash_flag = false;


	if(f_name == NULL)
	{
		fprintf(stderr,"Error while opening file\n");
		return 1;
	}

	const char *sql_request = "SELECT f_name, f_hash FROM flcn_hashes";
	
	if((sqlite3_open_v2(flcn_save_init->full_db_path, &db, SQLITE_OPEN_READWRITE, NULL)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite error: Failed opening DB for verify: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	if((sqlite3_prepare_v2(db, sql_request, -1, &stmt, NULL) != SQLITE_OK))
	{
		fprintf(stderr, "SQLite error: Error while preparing SQL statement: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	const char *f_hash = flcn_256_hash(f_name);	
	if(f_hash == NULL)
	{
		free(flcn_save);
		printf("Error opening file to calculate Hash\n");
		return 1;
	}

	while((sqlite3_step(stmt)) == SQLITE_ROW)
	{
		cmp_info cmp;
		cmp.f_name = strdup((const char *)sqlite3_column_text(stmt, 0));
		cmp.hash   = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(strcmp(cmp.f_name, basename(f_name)) == 0)
		{
			printf("File Name: \033[32mOK!\033[0m\n");
			fflush(stdout);
			f_name_flag = true;
		}

	
		if(strcmp(cmp.hash, f_hash) == 0)
		{
			printf("File Hash: \033[32mOK!\033[0m\n");
			fflush(stdout);
			f_hash_flag = true;
		}

		free(cmp.f_name);
		free(cmp.hash);
	}

	if(f_name_flag == true && f_hash_flag == false)
	{
		printf("\033[31mFailed\033[0m: A file with this name was found in database, but the hash does not match, the file may be different or corrupted\n");
	}


	if(f_name_flag == false && f_hash_flag == true)
	{ 
		printf("\033[33mNotice\033[0m: This file was found in database but with a different name\n"); 
	}

	sqlite3_finalize(stmt);

	if(db)
		sqlite3_close(db);

	if(flcn_save)
		free(flcn_save);

	return 0;
}
