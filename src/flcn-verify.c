#include "falconinit.h"


typedef struct Compare_att
{
	char *hash;
	char *f_name;

}cmp_info;

int flcn_verify(const char *f_name)
{
	struct dirent *dir;

	if(f_name == NULL)
	{
		fprintf(stderr,"Error while opening file\n");
		return 1;
	}

	flcn_save *flcn_save = malloc(sizeof *flcn_save);	

	bool f_name_flag = false;
	bool f_hash_flag = false;

	sqlite3 *db;
	sqlite3_stmt *stmt;
	
	const char *sql_request = "SELECT f_name, f_hash FROM flcn_hashes";
	
	int sql_op = sqlite3_open_v2(flcn_save_init->full_db_path, &db, SQLITE_OPEN_READWRITE, NULL);
	if(sql_op != SQLITE_OK)
	{
		fprintf(stderr, "SQLite error: Failed opening DB for verify: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	int sql_prep = sqlite3_prepare_v2(db, sql_request, -1, &stmt, NULL);
	if(sql_prep != SQLITE_OK)
	{
		fprintf(stderr, "SQLite error: Error while preparing SQL statement: %s\n", sqlite3_errmsg(db));
		return 1;
	}
	
	flcn_save->f_hash = flcn_256_hash(f_name);	
	if(flcn_save->f_hash == NULL)
	{
		free(flcn_save);
		printf("Error opening file to calculate Hash\n");
		return 1;
	}

	while((sql_prep = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		cmp_info cmp;
		cmp.f_name = strdup((const char *)sqlite3_column_text(stmt, 0));
		cmp.hash   = strdup((const char *)sqlite3_column_text(stmt, 1));

		if(strcmp(cmp.f_name, f_name) == 0)
		{
			printf("File Name: \033[32mOK!\033[0m\n");
			fflush(stdout);
			f_name_flag = true;
		}

	
		if(strcmp(cmp.hash, flcn_save->f_hash) == 0)
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

	if(sql_prep != SQLITE_DONE)
	{
		fprintf(stderr, "SQLite step err: %s", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return SQLITE_OK;
}
