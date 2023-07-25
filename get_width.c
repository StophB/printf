#include "main.h"

/**
 * get_width - determines the width
 *
 * @format: string in which to print the args
 *
 * @i: args to be evaluated
 *
 * @list: list of args
 *
 * Return: returns the width
 */

	int get_width(const char *format, int *i, va_list list)
	{
		int arg;
		int width = 0;

		for (arg = *i + 1; format[arg] != '\0'; arg++)
		{
			if (is_digit(format[arg]))
			{
				width *= 10;
				width += format[arg] - '0';
			}
			else if (format[arg] == '*')
			{
				arg++;
				width = va_arg(list, int);
				break;
			}
			else
				break;
		}

		*i = arg - 1;

		return (width);
	}
