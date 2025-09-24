//
// Created by revolver-ocelot on 9/22/25.
//

#ifndef FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H
#define FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H

#include <sqlite3.h>

int flcn_create_db(sqlite3 **db);
int flcn_save_name_and_hash_in_db(char *file, sqlite3 *db);
int flcn_close_db(sqlite3 *db);

#endif //FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H