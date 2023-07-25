#include "main.h"

/**
 * get_precision - determines the precision to print
 *
 * @format: string in which to print the args
 *
 * @i: args to be evaluated
 *
 * @list: list of args
 *
 * Return: returns the precision
 */

	int get_precision(const char *format, int *i, va_list list)
	{
		int arg = *i + 1;
		int precision = -1;

		if (format[arg] != '.')
			return (precision);

		precision = 0;

		for (arg += 1; format[arg] != '\0'; arg_i++)
		{
			if (is_digit(format[arg]))
			{
				precision *= 10;
				precision += format[arg] - '0';
			}
			else if (format[arg] == '*')
			{
				arg++;
				precision = va_arg(list, int);
				break;
			}
			else
				break;
		}

		*i = arg - 1;

		return (precision);
	}
