#include "flcn-hashes-handler.h"
#include "flcn_database_operations.h"

int flcn_create_db_to_save(const char *db_path, sqlite3 **db, sqlite3_stmt **stmt)//This must be called before the next function
{
	flcn_dboperations_open_db( db_path, db, FLCN_SQLITE_OPEN_CR | FLCN_SQLITE_OPEN_RW);//add error handling
	flcn_dboperations_prepare_db(*db, FLCN_SQLITE_CREATE_TABLE, stmt);
	flcn_dboperations_step_db(*stmt);
	flcn_dboperations_finalize_db_stmt(*stmt);
	return 0;
}

int flcn_save_in_db(char *file_name, sqlite3 *db, sqlite3_stmt *stmt )
{
	const char *file_hash = flcn_build_hash(file_name, EVP_sha256());

	flcn_dboperations_prepare_db(db, FLCN_SQLITE_INSERT_TABLE, &stmt);
	flcn_dboperations_db_bind_text(stmt, 1, file_name);
	flcn_dboperations_db_bind_text(stmt, 2, file_hash);
	flcn_dboperations_step_db(stmt);
	flcn_dboperations_finalize_db_stmt(stmt);
	flcn_dboperations_close_db(db);
}