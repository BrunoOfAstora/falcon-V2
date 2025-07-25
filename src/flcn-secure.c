#include "falconinit.h"

bool sec_strcmp(const char *str1, const char *str2, const size_t size)
{
	if(str1 == NULL || str2 == NULL)
		return false;

	volatile unsigned char result = 0;
	size_t i = 0;	

	while(i < size)
	{
		result |= (unsigned char)(str1[i] ^ str2[i]);
		i++;
	}
	
	return result == 0;
}

bool sec_memcmp(const void *blk1, const void *blk2, const size_t size)
{
	if(blk1 == NULL || blk2 == NULL)
		return false;

	const unsigned char *p1 = (const unsigned char*)blk1;
	const unsigned char *p2 = (const unsigned char*)blk2;

	volatile unsigned char result = 0;
	size_t i = 0;

	while(i < size)
	{
		result |= p1[i] ^ p2[i];
		i++;
	}
	
	return result == 0;
	
}
