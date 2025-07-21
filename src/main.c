#include "falconinit.h"

int main(int argc, char *argv[])
{
	int ret_num = -1;

	_save_init();

	if(argc < 2)
	{
		goto end;
	}
	
	int opt,
		opt_index;

	while(1)
	{
	//	int opt_optind = optind ? optind : 1;  Unused for now;
		static struct option long_options[] = 
		{
			{"md5", 	required_argument, 	0, 'm'},
			{"sha256", 	required_argument, 	0, '2'},
			{"sha384", 	required_argument,	0, '3'},
			{"sha512", 	required_argument,	0, '5'},
			{"save",    required_argument, 	0, 's'},
			{"verify", 	required_argument,  0, 'v'},
			{"rmdup", 	no_argument,  		0, 'r'},
			{"help", 	no_argument,		0, 'h'},				
			{0, 		0, 					0,  0 },
		};

		opt = getopt_long(argc, argv, "m:2:3:5:s:v:rh", long_options, &opt_index);
		if(opt == -1)
				break;

		switch(opt)
		{
			case 0:
				printf("options %s, ", long_options[opt_index].name);
				if(optarg)
					printf(" arguments %s", optarg);
				break;

			case 'm':
				printf("Calculating Hash MD5...");
				fflush(stdout);

				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: md5 option require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}
				
				char *md5_print = flcn_md5_hash(argv[2]);
				if(md5_print == NULL)
				{
					printf("The file don't exist or can't be opened\n");
					return -1;
				}
	

				if(md5_print == NULL)
				{
					printf("The file don't exist or can't be opened\n");
					return -1;
				}

				printf("\033[32mDONE!\033[0m\n");
				printf("MD5: %s\n", md5_print);

				break;


			case '2':
				printf("Calculating SHA256...");
				fflush(stdout);
				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: sha256 option require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}
			
				char *sha256_print = flcn_256_hash(argv[2]);

				if(sha256_print == NULL)
				{
					printf("The file don't exist or can't be opened\n");
					return -1;
				}

				printf("SHA256: %s\n", sha256_print);
				printf("\033[32mDONE!\033[0m\n");
				break;


			case '3':
				printf("Calculating SHA384...");
				fflush(stdout);

				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: sha384 option require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}

				char *sha384_print = flcn_384_hash(argv[2]);

				if(sha384_print == NULL)
				{
					printf("The file don't exist or can't be opened\n");
					return -1;
				}

				printf("\033[32mDONE!\033[0m\n");
				printf("SHA384: %s\n", sha384_print);
				break;


			case '5':
				printf("Calculating SHA512...");
				fflush(stdout);

				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: sha512 option require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}
				char *sha512_print = flcn_512_hash(argv[2]);

				if(sha512_print == NULL)
				{
					printf("The file don't exist or can't be opened\n");
					return -1;
				}

				printf("\033[32mDONE!\033[0m\n");
				printf("SHA512: %s\n", sha512_print);
				break;


			case 's':
				printf("Saving Hashes...");
				fflush(stdout);
		
				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: the 'save' function require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}
				
				int save_func_status = save_in_db(argv[2]);
				if(save_func_status != 0)
				{
					perror("Error in 'save' function. The File Name and File Hash are not saved in Data Base");
					break;
				}
				printf("\033[32mDONE\033[0m\n");

				break;


			case 'v':
				printf("Verifying Hash in DataBase...\n");
				
				if(optarg[0] == '-')
				{
					fprintf(stderr, "Error: the 'verify' function require a file as argument, but got '%s' as argument instead\n", optarg);
						return -1;
				}

//				if(argv[2])
				
				int verify_func_status = flcn_verify(argv[2]);
				if(verify_func_status != 0)
				{
					printf("Error while verifying hashes. The file hash mismatch the original file\n");
						return -1;
				}

				break;


			case 'r':
				printf("Removing duplicates...\n");
				fflush(stdout);
					
				int rm_dup = rmdup();
				if(rm_dup != 0)
				{
					perror("Error while removing duplicates\n");
					break;
				}
				printf("\033[32mDONE\033[0m\n");

				break;


			case 'h':
				printf("Help:\n	Options =>\n");
				printf("-m or --md5				Return hash md5 of file\n");
				printf("-2 or --sha256			Return hash SHA256 of file\n");
				printf("-3 or --sha384			Return hash SHA384 of file\n");
				printf("-5 or --sha512			Return hash SHA512 of file\n");	
				printf("-s or --save			Save the file name and file hash in the data base\n");
							
				break;

			default:
				printf("\nType 'falcon -h' or 'falcon --help' to see how to use falcon\n");
		}

	}
	if(optind < argc)
	{
		printf("No options for: ");	
		while(optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}
	
	exit(EXIT_SUCCESS);
	_save_deinit();
	ret_num = 0;

end: //maybe useless for now
	return ret_num;
}
