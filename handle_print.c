#include "main.h"
/**
 * handle_print - prints an arg based on type
 * @format:  string in which to print the args
 *
 * @list: list of args to be evaluated
 *
 * @ind: ind
 *
 * @buffer: buffer array
 *
 * @flags: calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: returns 1 or 2
 */

	int handle_print(const char *format, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
	{
			int k, unknow_len = 0, printed_chars = -1;
			format_t format_types[] = {
			{'c', print_char}, {'s', print_string}, {'%', print_percent},
			{'i', print_int}, {'d', print_int}, {'b', print_binary},
			{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
			{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
			{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
		};
		for (k = 0; format_types[k].format != '\0'; k++)
			if (format[*ind] == format_types[k].format)
				return (format_types[k].fn(list, buffer, flags, width, precision, size));

			if (format_types[k].format == '\0')
			{
			if (format[*ind] == '\0')
				return (-1);
			unknow_len += write(1, "%%", 1);
			if (format[*ind - 1] == ' ')
				unknow_len += write(1, " ", 1);
			else if (width)
			{
				--(*ind);
				while (format[*ind] != ' ' && format[*ind] != '%')
					--(*ind);
				if (format[*ind] == ' ')
					--(*ind);
				return (1);
			}
			unknow_len += write(1, &format[*ind], 1);
			return (unknow_len);
			}
		return (printed_chars);
	}
