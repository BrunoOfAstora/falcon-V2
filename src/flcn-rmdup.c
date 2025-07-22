#include "falconinit.h"

typedef struct temp
{
	char hash[65];
	char fname[FILENAME_MAX];
	UT_hash_handle hh;

}temp_t;

temp_t *hm = NULL;

int rmdup()
{
	int ret_code = 1;
	unsigned int f_deleted_count = 0;

	DIR *dirstr; //dir stream
	struct dirent *dir;
	
	dirstr = opendir(".");

	if(!dirstr)
	{
		printf("Can't open current directory\n");
		goto ret;
	}

	while((dir = readdir(dirstr)) != NULL)
	{
		if(dir->d_type == DT_REG)
		{
			const char *curr_fname = dir->d_name;
			char *curr_hash = flcn_256_hash(curr_fname);
			if(curr_hash == NULL)
				continue;
			
			temp_t *temp;

			HASH_FIND_STR(hm, curr_hash, temp);
			
			if(temp == NULL)
			{
				temp = malloc(sizeof *temp);
				
				strncpy(temp->fname, curr_fname, FILENAME_MAX);
				temp->fname[sizeof(temp->fname) - 1] = '\0';

				strncpy(temp->hash, curr_hash, 65);
				temp->hash[sizeof(temp->hash) - 1] = '\0';

				HASH_ADD_STR(hm, hash, temp);
			}
	
			else
			{
				remove(curr_fname);
				f_deleted_count++;
				printf("\n\x1b[31m->Removed:\x1b[0m %s (same: %s)\n", curr_fname, temp->fname);	
			}
			printf("Checking %s...\n", dir->d_name);
		}
	}

	temp_t *curr_entry, *tmp;
	HASH_ITER(hh, hm, curr_entry, tmp)
	{
		HASH_DEL(hm, curr_entry);
		free(curr_entry);
	}
	
	ret_code = 0;
	
ret: 	
	printf("%d duplicated files deleted.\n", f_deleted_count);		

	if(dirstr)
		closedir(dirstr);

	return ret_code;
}
