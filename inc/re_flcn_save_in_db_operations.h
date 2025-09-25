//
// Created by revolver-ocelot on 9/22/25.
//

#ifndef FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H
#define FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H

#include <sqlite3.h>

int re_save_in_db_create(sqlite3 **db);
int re_save_in_db_insert(sqlite3 *db, char *file);

#endif //FALCON_V2_RE_FLCN_SAVE_IN_DB_OPERATIONS_H