//
// Created by revolver-ocelot on 9/22/25.
//

#include "../inc/re_flcn_sqlite_operations_handler.h"
#include <sys/stat.h>
#include <string.h>

int flcn_dboperations_open_db(const char *db_path, sqlite3 **db, int flags)
{
    return sqlite3_open_v2(db_path, db, flags, NULL);
}

int flcn_dboperations_prepare_db(sqlite3 *db, const char *request, sqlite3_stmt **stmt)
{
    return sqlite3_prepare_v2(db, request, -1, stmt, NULL);
}

int flcn_dboperations_db_bind_text(sqlite3_stmt *stmt, int pos,const char *file_name)
{
    return sqlite3_bind_text(stmt, pos, file_name, -1, SQLITE_TRANSIENT);
}

int flcn_dboperations_step_db(sqlite3_stmt *stmt)
{
     return sqlite3_step(stmt);
}

int flcn_dboperations_finalize_db_stmt(sqlite3_stmt *stmt)
{
    return sqlite3_finalize(stmt);
}

int flcn_dboperations_close_db(sqlite3 *db)
{
    return sqlite3_close(db);
}

char *flcn_dboperations_column_strdup(sqlite3_stmt *stmt, int column)
{
    return strdup((const char *)sqlite3_column_text(stmt, column));
}