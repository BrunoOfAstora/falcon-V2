// 	flcn-init.c

#include "falconinit.h"


char *flcn_GetHomeDir()
{
	char *path_to_home_dir = getenv("HOME");
	if(!path_to_home_dir)
	{
		perror("Failed to get HOME directory\n");
		return NULL;
	}
	
	return path_to_home_dir;
}


size_t flcn_SetHashDirInHome(char *out_path, size_t size)
{

	const char *home = flcn_GetHomeDir();
	if(!home)
		return 1;

	if(snprintf(out_path, size, "%s/%s/", flcn_GetHomeDir(), "falcon-hashes") >= PATH_MAX)
		return 1;

	return 0;
}



size_t flcn_CreateDbFile(char *out_path, size_t size)
{
	char hash_dir[PATH_MAX];

	if(flcn_SetHashDirInHome(hash_dir, sizeof(hash_dir)) != 0)
		return 1;

	if(snprintf(out_path, size, "%s%s", hash_dir, "falcon_file_hash.db") >= PATH_MAX)
		return 1;

	return 0;
}
