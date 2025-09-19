#include "falconinit.h"
#include "flcn_init_db_path.h"

char *flcn_get_home_dir()
{
	return getenv("HOME");
}

void flcn_build_db_path(char *dbpath, size_t size, char *home_path)
{
	if (!home_path)
		home_path = "/tmp";
	snprintf(dbpath, size, "%s/%s/", home_path, ".falcon-hashes");
	mkdir(dbpath, 0700);
}

void flcn_build_file_in_db_path(char *db_path, size_t size, const char *filename)
{
	size_t len = strnlen(db_path, size);
	snprintf(db_path + len, size - len, "%s",filename);
}

void flcn_create_db_file(const char *db_path)
{
	FILE *f = fopen(db_path, "a+");
	fclose(f);
}

char *flcn_get_db_file_location(const char *db_path)
{
	return db_path;
}