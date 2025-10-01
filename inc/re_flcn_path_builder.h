//
// Created by revolver-ocelot on 9/22/25.
//

#ifndef FALCON_V2_RE_FLCN_PATH_BUILDER_H
#define FALCON_V2_RE_FLCN_PATH_BUILDER_H

char * flcn_get_home_dir();

char * flcn_build_path_to_db(char *home_dir, char *database_dest); //you can use this like: char * x = flcn_build_path_to_db(flcn_get_home_dir(), x);

char * flcn_get_real_path(const char *file_name);

#endif //FALCON_V2_RE_FLCN_PATH_BUILDER_H