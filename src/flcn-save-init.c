#include "falconinit.h"

flcn_save *flcn_save_init = NULL;
//flcn_save *flcn_save = NULL;

void _save_init()
{
	struct stat sb;
	
	if(flcn_save_init)
		return;
	
	flcn_save_init = malloc(sizeof *flcn_save_init);
	memset(flcn_save_init, 0, sizeof *flcn_save_init);

	flcn_save_init->curr_dir = NULL;		
	flcn_save_init->file_usr_stream = NULL;	
	flcn_save_init->f_all_name = NULL;
	flcn_save_init->f_hash = NULL;

	if(flcn_SetHashDirInHome(flcn_save_init->hash_folder_path, sizeof(flcn_save_init->hash_folder_path)) != 0)
	{
		perror("Failed to set a folder in Home Directory for save file hashes.\n");
		return;
	}	

	if(mkdir(flcn_save_init->hash_folder_path, 0755) == -1)
	{
		if(stat(flcn_save_init->hash_folder_path, &sb) == 0 && S_ISDIR(sb.st_mode)){}
	
		else
		{
			perror("Error while creating Directory to save hashes\n");
			return;
		}
	}

	if(flcn_CreateDbFile(flcn_save_init->full_db_path, sizeof(flcn_save_init->full_db_path)) != 0)
	{
		perror("Failed to set a file in Home Directory for save hashes.\n");
		return;
	}

	return;
}



void _save_deinit(void)
{
	if(flcn_save_init)
		free(flcn_save_init);

}
