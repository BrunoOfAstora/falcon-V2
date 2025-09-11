#include "falconinit.h"
#include "flcn-hashes.h"

int main(int argc, char *argv[])
{
    int ret_num = -1;

    _save_init();

    if(argc < 2)
    {
        printf("Usage: %s [options] <file>\n", argv[0]); 
        goto end;
    }

    int opt;
    int opt_index;

    while(1)
    {
        static struct option long_options[] =
        {
            {"md5",     required_argument,  0, 'm'},
            {"sha256",  required_argument,  0, '2'},
            {"sha384",  required_argument,  0, '3'},
           // {"sha512",  required_argument,  0, '5'},
            {"save",    required_argument,  0, 's'},
            {"verify",  required_argument,  0, 'v'},
            {"rmdup",   no_argument,        0, 'r'},
			{"cmp",		required_argument,	0, 'c'},
            {"help",    no_argument,        0, 'h'},
            {0,         0,                  0,  0 },
        };

        opt = getopt_long(argc, argv, "m:2:3:s:v:rc:h", long_options, &opt_index);
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
            {
                printf("Calculating Hash MD5...");
                fflush(stdout);

                if(optarg[0] == '-')
                {
                    fprintf(stderr, "Error: md5 option require a file as argument, but got '%s' as argument instead\n", optarg);
                        return -1;
                }

                char *flcn_build_hash_md5 = flcn_build_hash(optarg, EVP_md5());
                if(flcn_build_hash_md5 == NULL)
                {
                    printf("The file doesn't exist or can't be opened, or an error occurred during hash calculation.\n");
                    return -1;
                }

                printf("\033[32mDONE!\033[0m\n");
                printf("MD5: %s\n", flcn_build_hash_md5);
                free(flcn_build_hash_md5);
                break;
            }

            case '2':
            {
                printf("Calculating hash...");
                fflush(stdout);
                if(optarg[0] == '-')
                {
                    fprintf(stderr, "Error: sha256 option require a file as argument, but got '%s' as argument instead\n", optarg);
                        return -1;
                }

                char *flcn_build_hash256 = flcn_build_hash(optarg, EVP_sha256());
                if(flcn_build_hash256 == NULL)
                {
                    printf("The file doesn't exist or can't be opened, or an error occurred during hash calculation.\n");
                    return -1;
                }

                printf("\033[32mDONE!\033[0m\n");
                printf("SHA256: %s\n", flcn_build_hash256);
                free(flcn_build_hash256);
                break;
            }

            case '3':
            {
                printf("Calculating SHA384...");
                fflush(stdout);

                if(optarg[0] == '-')
                {
                    fprintf(stderr, "Error: sha384 option require a file as argument, but got '%s' as argument instead\n", optarg);
                        return -1;
                }

                char *flcn_build_hash_sha384 = flcn_build_hash(optarg, EVP_sha384());
                if(flcn_build_hash_sha384 == NULL)
                {
                    printf("The file doesn't exist or can't be opened, or an error occurred during hash calculation.\n");
                    return -1;
                }

                printf("\033[32mDONE!\033[0m\n");
                printf("SHA384: %s\n", flcn_build_hash_sha384);
                free(flcn_build_hash_sha384);
                break;
            }

          /*  case '5':
            {
                printf("Calculating SHA512...");
                fflush(stdout);

                if(optarg[0] == '-')
                {
                    fprintf(stderr, "Error: sha512 option require a file as argument, but got '%s' as argument instead\n", optarg);
                        return -1;
                }
                char *sha512_print = flcn_512_hash(optarg); // Use optarg
                if(sha512_print == NULL)
                {
                    printf("The file doesn't exist or can't be opened, or an error occurred during hash calculation.\n");
                    return -1;
                }
			
                printf("\033[32mDONE!\033[0m\n");
                printf("SHA512: %s\n", sha512_print);
                free(sha512_print); 
                break;
            }
			*/			

            case 's':
                printf("Saving Hashes...");
                fflush(stdout);

                if(optarg[0] == '-')
                {
                    fprintf(stderr, "Error: the 'save' function require a file as argument, but got '%s' as argument instead\n", optarg);
                        return -1;
                }

                int save_func_status = save_in_db_all(optarg); 
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

                int verify_func_status = flcn_verify_all(optarg); 
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

			case 'c':
				printf("Comparing files...\n");
				fflush(stdout);

				flcn_cmp_hash(argv[2], argv[3]);

				break;

            case 'h':
                printf("Help:\n\tOptions =>\n");
                printf("-m or --md5              Return hash md5 of file\n");
                printf("-2 or --sha256           Return hash SHA256 of file\n");
                printf("-3 or --sha384           Return hash SHA384 of file\n");
               // printf("-5 or --sha512           Return hash SHA512 of file\n");
                printf("-s or --save             Save the file name and file hash in the data base\n");
                printf("-r or --rmdup            Iterates over current directory and remove duplicated files\n"); 
				printf("-c or --cmp				 Compare two given files\n");
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

    ret_num = 0; 

end: 
    _save_deinit(); 
    return ret_num; 
}
