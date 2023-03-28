/*
 * Auth: Rohan Sewraj
 * File: _printf.c
 */
#include "main.h"
#include <stdarg.h>
#include <stdio.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int j;
	int output = 0;
	int print_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list printlist;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(printlist, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			buffer[buff_ind++] = format[j];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[j], 1);*/
			print_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &j);
			width = get_width(format, &j, printlist);
			precision = get_precision(format, &j, printlist);
			size = get_size(format, &j);
			++j;
			output = handle_print(format, &j, printlist, buffer,
				flags, width, precision, size);
			if (output == -1)
				return (-1);
			print_chars += output;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(printlist);

	return (print_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}