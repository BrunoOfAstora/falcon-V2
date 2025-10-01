//
// Created by revolver-ocelot on 9/22/25.
//

#ifndef FALCON_V2_RE_FLCN_MAIN_HANDLER_H
#define FALCON_V2_RE_FLCN_MAIN_HANDLER_H

#include <getopt.h>
#include <openssl/evp.h>
#include <sys/stat.h>

#define FF fflush(stdout)

#define FLCN_MD5_OPT    "md5",      required_argument,  0, 'm'
#define FLCN_SHA256_OPT "sha256",   required_argument,  0, '2'
#define FLCN_SHA384_OPT "sha384",   required_argument,  0, '3'
#define FLCN_SHA512_OPT "sha512",   required_argument,  0, '5'
#define FLCN_SAVE_OPT   "save",     required_argument,  0, 's'
#define FLCN_VERIFY_OPT "verify",   required_argument,  0, 'v'
#define FLCN_RMDUP_OPT  "rmdup",    no_argument,        0, 'r'
#define FLCN_CMP_OPT    "cmp",		required_argument,	0, 'c'
#define FLCN_HELP_OPT   "help",     no_argument,        0, 'h'
#define FLCN_END_OPT    0,          0,                  0,  0

#define FLCN_SHORTOPTS "m:2:3:5:s:v:rc:h"

char * flcn_calculate_hash(const char *mode, const EVP_MD *md_hash);
void flcn_print_func_usage_msg();
void flcn_print_usage_msg(char *name);
int flcn_save_data_in_db(char *file);
int flcn_check_valid_file(const char *file, struct stat st);
int flcn_check_reg_file(const struct stat *st);

#endif //FALCON_V2_RE_FLCN_MAIN_HANDLER_H