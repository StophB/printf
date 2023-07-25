#include "main.h"
#include <stdio.h>

/**
 * print_unsigned - prints an unsigned number
 *
 * @types: list a of args
 *
 * @buffer: buffer array to handle print
 *
 * @flags:  calc active flags
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: size specifier
 *
 * Return: number of characters printed
 */

	int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';


	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
	}


/**
 * print_octal - prints an unsigned number
 *
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags: calcs active flags
 *
 * @width: width
 *
 * @precision: precision specs
 *
 * @size: size specifier
 *
 * Return: number of characters
 */

	int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
	}


/**
 * print_hexadecimal - prints an unsigned number
 *
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags: calcs active flags
 *
 * @width: width
 *
 * @precision: precision specs
 *
 * @size: size specifier
 *
 * Return: number of characters
 */
	int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

		return (print_hexa(types, "0123456789abcdef", buffer,
			flags, 'x', width, precision, size));
	}


/**
 * print_hexa_upper - prints an unsigned number
 *
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags: calcs active flags
 *
 * @width: width
 *
 * @precision: precision specs
 *
 * @size: size specifier
 *
 * Return: number of characters
 */

	int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));

	}


/**
 * print_hexa - prints a hexadecimal number (upper or lower case)
 *
 * @types: lists of args
 *
 * @map_to: array of values
 *
 * @buffer: buffer array
 *
 * @flags:  calcs active flags
 *
 * @flag_ch: calcs active flags
 *
 * @width: width
 *
 * @precision: precision specs
 *
 * @size: size specifier
 *
 * Return: number of characterss
 */

	int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
	{

	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
	}
