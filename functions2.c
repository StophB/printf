#include "main.h"
#include "stdio.h"

/**
 * print_pointer - prints value of a ptr variable
 *
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags: flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: size specifier
 *
 * Return: number of characters
 */

	int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

		char extra_c = 0, padd = ' ';
		int len = BUFF_SIZE - 2, length = 2, padd_start = 1;
		unsigned long num_addrs;
		char map_to[] = "0123456789abcdef";
		void *addrs = va_arg(types, void *);

		UNUSED(width);
		UNUSED(size);

		if (addrs == NULL)
			return (write(1, "(nil)", 5));

		buffer[BUFF_SIZE - 1] = '\0';
		UNUSED(precision);

		num_addrs = (unsigned long)addrs;

		while (num_addrs > 0)
		{
			buffer[len--] = map_to[num_addrs % 16];
			num_addrs /= 16;
			length++;
		}

		if ((flags & F_ZERO) && !(flags & F_MINUS))
			padd = '0';
		if (flags & F_PLUS)
			extra_c = '+', length++;
		else if (flags & F_SPACE)
			extra_c = ' ', length++;

		len++;


		return (write_pointer(buffer, len, length,
			width, flags, padd, extra_c, padd_start));

	}


/**
 * print_non_printable - prints the ascii codes
 *
 * @types: lists of args
 *
 * @buffer: buffer array
 *
 * @flags:  calcs flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: size specifier
 *
 * Return: number of characters
 */

	int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

		int k = 0, offset = 0;
		char *str = va_arg(types, char *);

		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);

		if (str == NULL)
			return (write(1, "(null)", 6));

		while (str[k] != '\0')
		{
			if (is_printable(str[k]))
				buffer[k + offset] = str[k];
			else
				offset += append_hexa_code(str[k], buffer, k + offset);

			k++;
		}

		buffer[k + offset] = '\0';

		return (write(1, buffer, k + offset));

	}


/**
 * print_reverse - prints reverse str
 *
 * @types: list of args
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

	int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

		char *str;
		int k, count = 0;

		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(size);

		str = va_arg(types, char *);

		if (str == NULL)
		{
			UNUSED(precision);

			str = ")Null(";
		}

		for (k = 0; str[k]; k++)
		;

		for (k = k - 1; k >= 0; k--)
		{
			char z = str[k];

			write(1, &z, 1);
			count++;
		}
		return (count);
	}


/**
 * print_rot13string - prints the rot13 string
 *
 * @types: lista of args
 *
 * @buffer: buffer array
 *
 * @flags:  calcs flags active
 *
 * @width: width
 *
 * @precision: precision spec
 *
 * @size: specifier size
 *
 * Return: printed characters
 */

	int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
	{

		char x;
		char *str;
		unsigned int k, j;
		int count = 0;
		char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

		str = va_arg(types, char *);
		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);

		if (str == NULL)
			str = "(AHYY)";
		for (k = 0; str[k]; k++)
		{
			for (j = 0; in[j]; j++)
			{
				if (in[j] == str[k])
				{
					x = out[j];
					write(1, &x, 1);
					count++;
					break;
				}
			}
			if (!in[j])
			{
				x = str[k];
				write(1, &x, 1);
				count++;
			}
		}
		return (count);
	}
