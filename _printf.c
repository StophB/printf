#include "main.h"
#include <stdio.h>

	void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - printf function
 *
 * @fmt: format characters
 *
 * Return: printed characters
 */

	int _printf(const char *fmt, ...)
	{
		int j, printed = 0, printed_chars = 0;
		int flags, width, precision, size, buff_ind = 0;
		va_list list;
		char buffer[BUFF_SIZE];

		if (fmt == NULL)
			return (-1);

		va_start(list, fmt);

		for (j = 0; fmt && fmt[j] != '\0'; j++)
		{
			if (fmt[j] != '%')
			{
				buffer[buff_ind++] = fmt[j];
				if (buff_ind == BUFF_SIZE)
					print_buffer(buffer, &buff_ind);

				printed_chars++;
			}
			else
			{
				print_buffer(buffer, &buff_ind);
				flags = get_flags(frmt, &j);
				width = get_width(fmt, &j, list);
				precision = get_precision(fmt, &j, list);
				size = get_size(fmt, &j);
				++j;
				printed = handle_print(fmt, &j, list, buffer,
					flags, width, precision, size);
				if (printed == -1)
					return (-1);
				printed_chars += printed;
			}
		}

		print_buffer(buffer, &buff_ind);

		va_end(list);

		return (printed_chars);
	}

/**
 * print_buffer - prints the contents the existing buffer
 *
 * @buffer: buffer array
 * @buff_ind: index args
 */

	void print_buffer(char buffer[], int *buff_ind)
	{
		if (*buff_ind > 0)
			write(1, &buffer[0], *buff_ind);

		*buff_ind = 0;
	}
