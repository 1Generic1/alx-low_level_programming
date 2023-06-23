#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - Prints anything
 * @format: List of types of arguments passed to the function
 *           c: char
 *           i: integer
 *           f: float
 *           s: char * (if the string is NULL, print (nil) instead)
 *           any other char should be ignored
 */

void print_all(const char * const format, ...)
{
	va_List args;
	unsigned int i = 0;
	char *str;
	char separator = ',';

	va_start(args, format);

	while (format && format[i])
	{
		switch (format[i])
		{
			case 'c':
				printf("%c", va_arg(args, int));
				break;
			case 'i':
				printf("%d", va_arg(args, int));
				break;
			case 'f':
				printf("%f", va_arg(args, double));
				break;
			case 's':
				str = va_arg(args, char *);
				if (str == NULL)
					str = "(nil)";
				printf("%s", str);
				break;
			default:
				separator = 0;
				break;
		}
		if (format[i + 1] && separator)
			printf("%c ", separator);
		i++;
	}
	printf("\n");
	va_end(args);
}
