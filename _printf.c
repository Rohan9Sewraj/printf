/*
 * Auth: Rohan Sewraj
 * File: _printf.c
 */
#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int handle_print(const char *format, int *j, va_list printlist, char buffer[],
                 int flags, int width, int precision, int size);

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format string
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    if (format == NULL)
        return (-1);

    int j, output = 0, print_chars = 0, flags, width, precision, size, buff_ind = 0;
    va_list printlist;
    char buffer[BUFF_SIZE];

    va_start(printlist, format);

    for (j = 0; format[j] != '\0'; j++)
    {
        if (format[j] != '%')
        {
            buffer[buff_ind++] = format[j];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
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
            {
                va_end(printlist);
                return (-1);
            }
            print_chars += output;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(printlist);

    return (print_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: array of characters to print
 * @buff_ind: pointer to the index to add the next character
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
}

