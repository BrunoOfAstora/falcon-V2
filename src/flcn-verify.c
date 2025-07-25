#include "falconinit.h"
#include <sqlite3.h>

typedef struct Compare_att
{
	char *hash;
	char *f_name;

}cmp_info;

unsigned int f_err = 0;

int verify_callback(const char *f_path, const struct stat *st, int flag, struct FTW *ftwbuf)
{
	(void)st;    
    (void)ftwbuf; 	

	if(flag == FTW_F)
		flcn_verify((char *)f_path);

	/*else if (flag == FTW_D || flag == FTW_DP)
	{
	//	if(ftwbuf->level > 1)
			return FTW_SKIP_SUBTREE;
	}*/
	
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
	{
		nftw(start_path, verify_callback, 1, FTW_PHYS);
		printf("\n_______________________________\n");
		fflush(stdout);
		printf("Divergences found: %d", f_err);
		printf("\n_______________________________\n");
		fflush(stdout);
		return 0;
	}

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
	sqlite3 *db;
	sqlite3_stmt *stmt;
	cmp_info cmp;

	bool f_name_flag = false;
	bool f_hash_flag = false;


	if(f_name == NULL)
	{
		fprintf(stderr,"Error while opening file\n");
		return 1;
	}

	char *abs_f_name = realpath(f_name, NULL);
    if (abs_f_name == NULL) {
        perror("Error getting realpath");
        return 1;
    }

	const char *sql_request = "SELECT f_name, f_hash FROM flcn_hashes WHERE f_name = ?";
	
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
		printf("Error opening file to calculate Hash\n");
		return 1;
	}

	sqlite3_bind_text(stmt, 1, abs_f_name, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		cmp.f_name = strdup((const char *)sqlite3_column_text(stmt, 0));
		cmp.hash   = strdup((const char *)sqlite3_column_text(stmt, 1));

		size_t leng1 = strlen(cmp.f_name);
		size_t leng2 = strlen(abs_f_name);

		if(sec_memcmp(cmp.f_name, abs_f_name, leng1) == true && leng1 == leng2) 
			f_name_flag = true;
	
		if(sec_memcmp(cmp.hash, f_hash, 32) == true)
			f_hash_flag = true;
		
		free(cmp.f_name);
		free(cmp.hash);
	}

	printf("\n");
	printf("Checking %s...", basename(f_name));
	if(f_name_flag == true)
		printf("\033[32mOK!\033[0m\n");
	else
		printf("\033[31mFailed\033[0m\n");


	printf("Checking %s hash...", basename(f_name));
	if(f_hash_flag)
		printf("File Hash: \033[32mOK!\033[0m\n");
	else if(!f_name_flag && f_hash_flag)
		printf("\033[32mOK\033[0m\n\033[33mNotice\033[0m: This file was found in database but with a different name\n");
	else
	{
		f_err++;
		printf("\033[31mFailed\033[0m\n");
	}

	if(!f_name_flag && !f_hash_flag)
		printf("File not found in DB\n");

	if(f_name_flag && !f_hash_flag)
		printf("\033[31mFailed\033[0m: A file with name %s was found in database, but the hash does not match, the file may be different or corrupted\n", basename(f_name));

	sqlite3_finalize(stmt);

	if(db)
		sqlite3_close(db);

	return 0;
}
