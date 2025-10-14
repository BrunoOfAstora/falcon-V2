//
// Created by revolver-ocelot on 10/2/25.
//

#ifndef FALCON_V2_RE_FLCN_VERIFY_H
#define FALCON_V2_RE_FLCN_VERIFY_H
#include <sqlite3.h>

int flcn_verify(const char *file_name);
bool flcn_verify_all_files(const char *directory);

#endif //FALCON_V2_RE_FLCN_VERIFY_H