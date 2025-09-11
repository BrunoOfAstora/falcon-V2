#include "falconinit.h"
#include "flcn-hashes.h"
#include <sqlite3.h>


int save_in_db_callback(const char *f_path, const struct stat *st, int flag, struct FTW *ftwbuf)
{
	(void)st;
	(void)ftwbuf;

	if(flag == FTW_F)
		save_in_db((char *)f_path);

	return 0;
	
}


int save_in_db_all(const char *start_path)
{
	struct stat st;
	
	if(stat(start_path, &st) == -1)
	{
		perror("Start Failed:");
		return 1;
	}

	if(S_ISDIR(st.st_mode))
		return nftw(start_path, save_in_db_callback, 1, FTW_PHYS);

	if(S_ISREG(st.st_mode))
		return save_in_db((char *)start_path);

	else
	{
		printf("Unsupported file type\n");
		return 1;
	}
}


int save_in_db(char *f_name)
{
	int return_code = 1;

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

	flcn_save *flcn_save = malloc( sizeof *flcn_save );
	sqlite3 *db;
	sqlite3_stmt *stmt;

	const char *sql_create = "CREATE TABLE IF NOT EXISTS flcn_hashes (f_name TEXT PRIMARY KEY, f_hash TEXT NOT NULL)";
	const char *sql_insert = "REPLACE INTO flcn_hashes (f_name, f_hash) VALUES (?, ?)";


	if((sqlite3_open_v2(flcn_save_init->full_db_path, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (OPEN DB): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	if((sqlite3_prepare_v2(db, sql_create, -1, &stmt, NULL)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (create PREPARE): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	if((sqlite3_step(stmt)) != SQLITE_DONE)
	{
		fprintf(stderr, "SQLite Error, (create STEP): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	sqlite3_finalize(stmt);
	
	flcn_save->f_hash = flcn_build_hash(f_name, EVP_sha256());

	if((sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (save PREPARE): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	if((sqlite3_bind_text(stmt, 1, abs_f_name, -1, SQLITE_STATIC)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (bind text 1 error): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}	

	if((sqlite3_bind_text(stmt, 2, flcn_save->f_hash, -1, SQLITE_STATIC)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (bind text 2 error): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	if((sqlite3_step(stmt)) != SQLITE_DONE)
	{
		fprintf(stderr, "SQLite Error, (save STEP): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	if ((sqlite3_finalize(stmt)) != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (save FINALIZE): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	sqlite3_close(db);
	
	free(flcn_save);
	return_code = 0;
	
	
	return return_code;

end_func:
	
	if(db)
		sqlite3_close(db);
	
	if(flcn_save)
		free(flcn_save);

	return return_code;	
}
