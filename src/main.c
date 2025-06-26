#include "falconinit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


int main(int argc, char *argv[])
{
	int ret_num = -1;

	if(argc < 2)
	{
		printf("\nLess than one argument, use 'falcon -h'\n");
		goto end;
	}
	
	
	const char *md5test = flcn_512_hash(argv[1]);
	printf("MD5 = %s\n",md5test);

	ret_num = 0;

end:
	return ret_num;


place_holder:
	printf("\nPlace Holder Function Example\n");
	return 10;

}
