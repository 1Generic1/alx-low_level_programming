#include "main.h"

/**
 * _atoi - Entry point
 * @s: string to be converted to integer
 *
 */
int _atoi(char *s)
{
	int sign = 1, result = 0;

	while (*s) 
	{
		if (*s == '-')
			sign = -sign;
		else if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');
		else if (result > 0)
			break;
		++s;
	}
	return (sign*result);
}
