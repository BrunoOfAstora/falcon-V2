#include "falconinit.h"

int save_in_db(char *f_name)
{
	int return_code = 1;

	struct FalconSaveInit *flcn_save = malloc( sizeof( struct FalconSaveInit ));
	struct dirent *dir;
	struct stat sb;
	sqlite3 *db;
	sqlite3_stmt *stmt;

	const char *sql_create = "CREATE TABLE IF NOT EXISTS flcn_hashes (flcn_hashes_id INTEGER PRIMARY KEY, f_name TEXT, f_hash TEXT UNIQUE)";
	const char *sql_insert = "INSERT OR IGNORE INTO flcn_hashes (f_name, f_hash) VALUES (?, ?)";

	char *home_path = getenv("HOME");
	if(!home_path)
	{
		perror("Failed to get HOME directory\n"); //maybe create in current dir if home not found (?)
		goto end_func;
	}
	
	snprintf(flcn_save->hash_folder_path, sizeof(flcn_save->hash_folder_path), "%s/%s/",home_path, "falcon-hashes");


	if(mkdir(flcn_save->hash_folder_path, 0755) == -1)
	{
		if(stat(flcn_save->hash_folder_path, &sb) == 0 && S_ISDIR(sb.st_mode)){}
	
		else
		{
			perror("Error while creating Directory to save hashes\n");
			goto end_func;
		}

	}

	snprintf(flcn_save->full_db_path, sizeof(flcn_save->full_db_path), "%s%s", flcn_save->hash_folder_path, "falcon_file_hash.db");

	int sql_op = sqlite3_open_v2(flcn_save->full_db_path, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	if(sql_op != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (OPEN DB): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	int sql_prepare_create = sqlite3_prepare_v2(db, sql_create, -1, &stmt, NULL);
	if(sql_prepare_create != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (create PREPARE): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	int sql_step_create = sqlite3_step(stmt);
	if(sql_step_create != SQLITE_DONE)
	{
		fprintf(stderr, "SQLite Error, (create STEP): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	sqlite3_finalize(stmt);
	

	if(strcmp(f_name, ".") == 0)
	{
		flcn_save->curr_dir = opendir(".");
		if(flcn_save->curr_dir)
		{
			while((dir = readdir(flcn_save->curr_dir)) != NULL)
			{
				if(dir->d_type == DT_REG)
				{
					flcn_save->f_all_name = dir->d_name;
					flcn_save->f_hash = flcn_384_hash(flcn_save->f_all_name);

					int sql_save_all_prepare = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
					if(sql_save_all_prepare != SQLITE_OK)
					{
						fprintf(stderr, "SQLite Error, (save all BIND TEXT 1): %s\n", sqlite3_errmsg(db));
						continue;
					} 

					int sql_save_all_fname = sqlite3_bind_text(stmt, 1, flcn_save->f_all_name, -1, SQLITE_STATIC);
					if(sql_save_all_fname != SQLITE_OK)
					{
						fprintf(stderr, "SQLite Error, (save all BIND TEXT 1): %s\n", sqlite3_errmsg(db));
						continue;
					}

					int sql_save_all_fhash = sqlite3_bind_text(stmt, 2, flcn_save->f_hash, -1, SQLITE_STATIC);
					if(sql_save_all_fhash != SQLITE_OK)
					{
						fprintf(stderr, "SQLite Error, (save all BIND TEXT 2): %s\n", sqlite3_errmsg(db));
						continue;
					}

					int sql_save_all_step = sqlite3_step(stmt);
					if(sql_save_all_step != SQLITE_OK)	
						continue;
					
					int sql_save_all_finalize = sqlite3_finalize(stmt);
					if(sql_save_all_finalize != SQLITE_OK)
					{
						fprintf(stderr, "SQLite Error, (save all FINALIZE): %s\n", sqlite3_errmsg(db));
						continue;
					}
				}
			}
		}
		return_code = 0;
		goto end_func;
	}

	flcn_save->f_hash = flcn_384_hash(f_name);

	int sql_save_prepare = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
	if(sql_save_prepare != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (save PREPARE): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	int sql_save_fname = sqlite3_bind_text(stmt, 1, f_name, -1, SQLITE_STATIC);
	if(sql_save_fname != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (bind text 1 error): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}	

	int sql_save_fhash = sqlite3_bind_text(stmt, 2, flcn_save->f_hash, -1, SQLITE_STATIC);
	if(sql_save_fhash != SQLITE_OK)
	{
		fprintf(stderr, "SQLite Error, (bind text 2 error): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	int sql_save_step = sqlite3_step(stmt);
	if(sql_save_step != SQLITE_DONE)
	{
		fprintf(stderr, "SQLite Error, (save STEP): %s\n", sqlite3_errmsg(db));
		goto end_func;
	}

	int sql_save_finalize = sqlite3_finalize(stmt);
	if(sql_save_finalize != SQLITE_OK)
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
