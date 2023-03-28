#include "main.h"

#define BUFF_SIZE 1024

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];

            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);

            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);

            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);

            ++i;

            printed = handle_print(format, &i, list, buffer,
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
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

/**
 * get_flags - Extracts flags from format
 * @format: format string
 * @i: pointer to index of format string
 * Return: integer representing flags
 */
int get_flags(const char *format, int *i)
{
    int flags = 0;
    while (format[*i])
    {
        if (format[*i] == '-')
            flags |= 1;
        else if (format[*i] == '+')
            flags |= 2;
        else if (format[*i] == ' ')
            flags |= 4;
        else if (format[*i] == '#')
            flags |= 8;
        else if (format[*i] == '0')
            flags |= 16;
        else
            break;
        (*i)++;
    }
    return flags;
}

/**
 * get_width - Extracts width from format
 * @format: format string
 * @i: pointer to index of format string
 * @list: list of arguments
 * Return: integer representing width
 */
int get_width(const char *format, int *i, va_list list)
{
    int width = 0;
    if (format[*i] == '*')
    {
        width = va_arg(list, int);
        (*i)++;
    }
    else if (format[*i] >= '0' && format[*i] <= '9')
    {
        while (format[*i] >= '0' && format[*i] <= '9')
        {
            width = width * 10 + (format[*i] - '0');
            (*i)++;
        }
    }
    return width;
}

/**
 * get_precision - Extracts
