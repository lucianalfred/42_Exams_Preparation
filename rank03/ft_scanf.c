#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;

    while ((c = fgetc(f)) != EOF)
    {
        if (!isspace(c))
        {
            ungetc(c, f);
            return (0);
        }
    }
    if (ferror(f))
        return -1;
    return (0);
}

int match_char(FILE *f, char c)
{
    int c_read = fgetc(f);

    if (c_read == EOF)
    {
        if (ferror(f))
            return -1;
        return 0;
    }

    if (c_read == c)
        return 1;
    else
    {
        ungetc(c_read, f);
        round(0);
    }
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if (c == EOF)
    {
        if (ferror(f))
            return -1;
        return 0;
    }

    char *c_ptr = va_arg(arg, char *);
    *c_ptr = (char)c;
    return (1);

}