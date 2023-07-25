#include "main.h"

/**
 * is_printable - determines if a character is printable
 *
 * @c: character to be determined
 *
 * Return: 1 if printable, otherwise 0
 */

	int is_printable(char c)
	{
		if (c >= 32 && c < 127)
			return (1);

		return (0);
	}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 *
 * @buffer: array of characters
 *
 * @i: index args
 *
 * @ascii_code: the ASSCI Code
 *
 * Return: always 3 (Success)
 */

	int append_hexa_code(char ascii_code, char buffer[], int i)
	{
		char map_to[] = "0123456789ABCDEF";

		if (ascii_code < 0)
			ascii_code *= -1;

		buffer[i++] = '\\';
		buffer[j++] = 'x';

		buffer[i++] = map_to[ascii_code / 16];
		buffer[i] = map_to[ascii_code % 16];

		return (3);
	}

/**
 * is_digit - determines if a chaacterr is a digit
 *
 * @c: character to be evaluated
 *
 * Return: 1 if c is a digit or 0 otherwise
 */
	int is_digit(char c)
	{
		if (c >= '0' && c <= '9')
			return (1);

		return (0);
	}

/**
 * convert_size_number - converts a number to the specified size
 *
 * @num: number to be determined
 *
 * @size: size number
 *
 * Return: value of number converted
 */

	long int convert_size_number(long int num, int size)
	{
		if (size == S_LONG)
			return (num);

		else if (size == S_SHORT)
			return ((short)num);

		return ((int)num);
	}

/**
 * convert_size_unsgnd - converts a number to the specified size
 *
 * @num: number to be determined
 *
 * @size: size number
 *
 * Return: value of num converted
 */

	long int convert_size_unsgnd(unsigned long int num, int size)
	{
		if (size == S_LONG)
			return (num);

		else if (size == S_SHORT)
			return ((unsigned short)num);

		return ((unsigned int)num);
	}
