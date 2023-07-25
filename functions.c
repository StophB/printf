#include "main.h"


/**
 * print_char - Prints a character
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char r = va_arg(types, int);

	return (handle_write_char(r, buffer, flags, width, precision, size));
}

/**
 * print_string - prints a string
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, k;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - prints the percentage sign
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */
	int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{
		UNUSED(types);
		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);
		return (write(1, "%%", 1));
	}


/**
 * print_int - prints the integer
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int z = va_arg(types, long int);
	unsigned long int num;

	z = convert_size_number(z, size);

	if (z == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)z;

	if (z < 0)
	{
		num = (unsigned long int)((-1) * z);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (write_number(is_negative, k, buffer, flags, width, precision, size));
}

/**
 * print_binary - prints a binary
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calc flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */
	int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{
		unsigned int n, j, k, sum;
		unsigned int a[32];
		int count;

		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);

		n = va_arg(types, unsigned int);
		j = 2147483648; /* (2 ^ 31) */
		a[0] = n / j;
		for (k = 1; k < 32; k++)
		{
			j /= 2;
			a[k] = (n / j) % 2;
		}
		for (k = 0, sum = 0, count = 0; k < 32; k++)
		{
			sum += a[k];
			if (sum || k == 31)
			{
				char z = '0' + a[k];

				write(1, &z, 1);
				count++;
			}
		}

		return (count);
	}
