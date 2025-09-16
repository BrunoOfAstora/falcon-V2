#include "falconinit.h"
#include "flcn-hashes.h"
#include "flcn_verify.h";

/*int flcn_verify_get_pat(const char *path)
{
	struct stat st;
	return stat(path, &st);
}
*/
char *flcn_verify_get_file_path(const char *file_name)
{
	char *rp = realpath(file_name, NULL);
	if (rp == NULL)
		return NULL;
	return rp;
}

// SQL Operations
int flcn_verify_init_db(sqlite3 **db, const char *db_path)
{
	return sqlite3_open_v2(db_path, db, SQLITE_OPEN_READWRITE, NULL);

}

int flcn_verify_prepare_db(sqlite3 *db, const char *request, sqlite3_stmt **stmt)
{
	return sqlite3_prepare_v2(db, request, -1, stmt, NULL);
}

int flcn_verify_db_bind_text(sqlite3_stmt *stmt, const char *file_name)
{
	return sqlite3_bind_text(stmt, 1, file_name, -1, SQLITE_STATIC);
}

int flcn_verify_step_db(sqlite3_stmt *stmt)
{
	int step = sqlite3_step(stmt);//is this easier to read? maybe?
	if (step == SQLITE_ROW) return FLCN_DB_ROW;
	if (step == SQLITE_DONE) return FLCN_DB_DONE;
	if (step == SQLITE_ERROR) return FLCN_DB_ERROR;
}

void flcn_verify_finalize_db_stmt(sqlite3_stmt *stmt)
{
	sqlite3_finalize(stmt);
}

void flcn_verify_close_db(sqlite3 *db)
{
	sqlite3_close(db);
}

char *flcn_verify_column_strdup(sqlite3_stmt *stmt, int column)
{
	return strdup((const char *)sqlite3_column_text(stmt, column));
}
// END SQL Operations
//

int flcn_verify_crypto_cmp(char *str1, char *str2, size_t len)
{
	return CRYPTO_memcmp(str1, str2, len);
}
//