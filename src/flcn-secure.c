#include "falconinit.h"

bool sec_strcmp(const char *str1, const char *str2, size_t size)
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
