#ifndef FALCON_V2_FLCN_DATABSE_OPERATIONS_DIGEST_H
#define FALCON_V2_FLCN_DATABSE_OPERATIONS_DIGEST_H
#include <sqlite3.h>

int flcn_create_db_to_save(const char *db_path, sqlite3 **db, sqlite3_stmt **stmt);

int flcn_save_in_db(char *file_name, sqlite3 *db, sqlite3_stmt *stmt );

#endif //FALCON_V2_FLCN_DATABSE_OPERATIONS_DIGEST_H