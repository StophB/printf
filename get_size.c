#include "main.h"
#include <stdio.h>

/**
 * get_size - determines the size
 *
 * @format: string in which to print args
 *
 * @i: args to be evaluated
 *
 * Return: the size
 */

	int get_size(const char *format, int *i)
	{
		int arg = *i + 1;
		int size = 0;

		if (format[arg] == 'l')
			size = S_LONG;

		else if (format[arg] == 'h')
			size = S_SHORT;

		if (size == 0)
			*i = arg - 1;
		else
			*i = arg;

		return (size);
	}
