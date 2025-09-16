#include "falconinit.h"
#include "flcn_init.h"

char *flcn_get_home_dir()
{
	return getenv("HOME");
}

void flcn_build_db_path(DbPath *dbpath, size_t size, char *home_path)
{
	if (!home_path)
		home_path = "/tmp";
	snprintf(dbpath->db_path_buf, size, "%s/%s/", home_path, ".falcon-hashes");
}

void *flcn_build_file_in_db_path(DbPath *db_path, size_t size, const char *filename)
{
	size_t len = strnlen(db_path->db_path_buf, size);
	snprintf(db_path->db_path_buf + len, size - len, "%s",filename);
}