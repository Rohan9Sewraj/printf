#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int i = 0;
    int count = 0;
    char c;

    while ((c = format[i++]))
    {
        if (c != '%')
        {
            putchar(c);
            count++;
        }
        else
        {
            switch (c = format[i++])
            {
                case 'c':
                    putchar(va_arg(args, int));
                    count++;
                    break;
                case 's':
                    count += printf(va_arg(args, const char *));
                    break;
                case '%':
                    putchar('%');
                    count++;
                    break;
                default:
                    printf("Invalid format specifier: %c", c);
                    return -1;
            }
        }
    }

    va_end(args);

    return count;
}
