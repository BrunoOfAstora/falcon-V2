//
// Created by revolver-ocelot on 9/22/25.
//

#include "../inc/re_flcn_main.h"
#include "../inc/re_flcn_main_handler.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [options] <file>\n", argv[0]);
        return -1;
    }

    int opt;
    int opt_ind;

    while (true)
    {
        static struct option long_options[] =
        {
            {FLCN_MD5_OPT},
            {FLCN_SHA256_OPT},
            {FLCN_SHA384_OPT},
            {FLCN_SHA512_OPT},
            {FLCN_END_OPT},
        };
        opt = getopt_long(argc, argv, FLCN_SHORTOPTS, long_options, &opt_ind);
        if (opt == -1) break;

        switch (opt)
        {
        case 0:
            printf("Options %s, ", long_options[opt_ind].name);
            if (optarg)
                printf(" arguments %s", optarg);
            break;

        case 'm':
            {
                char *hash = flcn_calculate_hash(optarg, EVP_md5());
                if (hash != NULL)
                    printf("MD5: %s\n", hash);
                break;
            }

        case '2':
            {
                char * hash = flcn_calculate_hash(optarg, EVP_sha256());
                if (hash != NULL)
                    printf("SHA256: %s\n", hash);
                break;
            }
        case '3':
            {
                char * hash = flcn_calculate_hash(optarg, EVP_sha384());
                if (hash != NULL)
                    printf("SHA384: %s\n", hash);
                break;
            }
        case '5':
            {
                char * hash = flcn_calculate_hash(optarg, EVP_sha512());
                if (hash != NULL)
                    printf("SHA512: %s\n", hash);
                break;
            }

        case 's':
            {
               printf("Saving HASH in DB...");
                if ((flcn_save_data_in_db(optarg)) != 0)
                {
                    printf("\n Error saving file.\n");
                    return -1;
                }
                printf("\033[32mDONE!\033[0m\n");
                break;
            }

        }
    }
}