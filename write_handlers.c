#include "main.h"

/**
 * handle_write_char - prints a string
 *
 * @c: types of character
 * @buffer: buffer array
 * @flags:  calculates flags that are active
 *
 * @width: width
 * @precision: precision spec
 * @size: specifier size
 *
 * Return: number of printed characters
 */

	int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
	{
		int j = 0;
		char padd = ' ';

		UNUSED(precision);
		UNUSED(size);

		if (flags & F_ZERO)
			padd = '0';

		buffer[j++] = c;
		buffer[j] = '\0';

		if (width > 1)
		{
			buffer[BUFF_SIZE - 1] = '\0';
			for (j = 0; j < width - 1; j++)
				buffer[BUFF_SIZE - j - 2] = padd;

			if (flags & F_MINUS)
				return (write(1, &buffer[0], 1) +
						write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
			else
				return (write(1, &buffer[BUFF_SIZE - j - 1], width - 1) +
					write(1, &buffer[0], 1));
		}

		return (write(1, &buffer[0], 1));
	}


/**
 * write_number - prints a number
 *
 * @is_negative: lists ofargs
 * @ind: types of character
 *
 * @buffer: buffer array
 * @flags: calc flags that are active
 * @width: width
 *
 * @precision: precision spec
 * @size: specifier size
 *
 * Return: printed character
 */
	int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
	{
		int len = BUFF_SIZE - ind - 1;
		char padd = ' ', extra_ch = 0;

		UNUSED(size);

		if ((flags & F_ZERO) && !(flags & F_MINUS))
			padd = '0';
		if (is_negative)
			extra_ch = '-';
		else if (flags & F_PLUS)
			extra_ch = '+';
		else if (flags & F_SPACE)
			extra_ch = ' ';

		return (write_num(ind, buffer, flags, width, precision,
			len, padd, extra_ch));
	}

/**
 * write_num - writes a number using bufffer
 * @ind: index args
 * @buffer: buffer array
 * @flags: flags
 * @width: width
 * @prec: precision spec
 * @len: number length
 * @padd: pading character
 * @extra_c: extra character
 * Return: printed characters
 */
	int write_num(int ind, char buffer[],
		int flags, int width, int prec,
		int len, char padd, char extra_c)
	{
		int k, padd_start = 1;

		if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
			return (0);
		if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
			buffer[ind] = padd = ' ';
		if (prec > 0 && prec < len)
			padd = ' ';
		while (prec > len)
			buffer[--ind] = '0', len++;
		if (extra_c != 0)
			len++;
		if (width > len)
		{
			for (k = 1; k < width - len + 1; k++)
				buffer[k] = padd;
			buffer[k] = '\0';
			if (flags & F_MINUS && padd == ' ')
			{
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[ind], len) + write(1, &buffer[1], k - 1));
			}
			else if (!(flags & F_MINUS) && padd == ' ')
			{
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[1], k - 1) + write(1, &buffer[ind], len));
			}
			else if (!(flags & F_MINUS) && padd == '0')
			{
				if (extra_c)
					buffer[--padd_start] = extra_c;
				return (write(1, &buffer[padd_start], k - padd_start) +
					write(1, &buffer[ind], len - (1 - padd_start)));
			}
		}
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], len));
	}

/**
 * write_unsgnd - writes an unsgnd number
 * @is_negative: determining if the number is -ve
 * @ind: index args
 * @buffer:buffer array
 * @flags: flags
 * @width: width
 * @precision: prec specifier
 * @size: specifier size
 *
 * Return: printed characters
 */

	int write_unsgnd(int is_negative, int ind,
		char buffer[],
		int flags, int width, int precision, int size)
	{
		int len = BUFF_SIZE - ind - 1, j = 0;
		char padd = ' ';

		UNUSED(is_negative);
		UNUSED(size);

		if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
			return (0);

		if (precision > 0 && precision < len)
			padd = ' ';

		while (precision > len)
		{
			buffer[--ind] = '0';
			len++;
		}

		if ((flags & F_ZERO) && !(flags & F_MINUS))
			padd = '0';

		if (width > len)
		{
			for (j = 0; j < width - len; j++)
			buffer[j] = padd;

			buffer[j] = '\0';

			if (flags & F_MINUS)
			{
				return (write(1, &buffer[ind], len) + write(1, &buffer[0], j));
			}
			else
			{
				return (write(1, &buffer[0], j) + write(1, &buffer[ind], len));
			}
		}

		return (write(1, &buffer[ind], len));
	}

/**
 * write_pointer - writes a pointer to a mem address
 * @buffer: buffer arrays
 * @ind: index args
 * @len: length of number
 * @width: width
 * @flags: flags
 * @padd: padding character
 * @extra_c: extra character
 * @padd_start: padding starting point
 * Return: printed characters
 */
	int write_pointer(char buffer[], int ind, int len,
		int width, int flags, char padd, char extra_c, int padd_start)
	{
		int k;

		if (width > len)
		{
			for (k = 3; k < width - len + 3; k++)
				buffer[k] = padd;
			buffer[k] = '\0';
			if (flags & F_MINUS && padd == ' ')
			{
				buffer[--ind] = 'x';
				buffer[--ind] = '0';
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[ind], len) + write(1, &buffer[3], k - 3));
			}
			else if (!(flags & F_MINUS) && padd == ' ')
			{
				buffer[--ind] = 'x';
				buffer[--ind] = '0';
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[3], k - 3) + write(1, &buffer[ind], len));
			}
			else if (!(flags & F_MINUS) && padd == '0')
			{
				if (extra_c)
					buffer[--padd_start] = extra_c;
				buffer[1] = '0';
				buffer[2] = 'x';
				return (write(1, &buffer[padd_start], k - padd_start) +
					write(1, &buffer[ind], len - (1 - padd_start) - 2));
			}
		}
		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
	}
