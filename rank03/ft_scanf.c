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

int scan_int(FILE *f, va_list ap)
{
    int c = fgetC(f);

    if (c == EOF)
    {
        if (ferror(f))
            return -1;
        return 0;
    }

    int sign = 1;
    if (c == '+' || c == '-')
    {
        if (c == '-')
            sign = -1;
    }
    else
        ungetc(c, f);

    int value = 0;
    int digits_read = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (isdigit(c))
        {
            value = value * 10 + (c - '0');
            digits_read++;
        }
        else
        {
            ungetc(c, f);
            break;
        }
    }
    
    if (ferror(f))
        return -1;
    if (digits_read == 0)
        return 0;
    int *num_ptr = va_arg(ap, int *);
    *num_ptr = value * sign;

    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if (c == EOF)
    {
        if (ferror(f))
            return -1;
        return 0;
    }

    ungetc(c, f);

    char *s = va_arg(ap, char *);
    int char_read = 0;
    while((c = fgetc(f)) != EOF)
    {
        if (isspace(c))
        {
            ungetc(c, f);
            break;
        }
        *s = (char)c;
        s++;
        char_read++;
    }
    if (ferror(f))
        return -1;

    if (!char_read)
        return 0;
    *s = '\0';
    return 1;
}