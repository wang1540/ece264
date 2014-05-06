include <stdlib.h>
include <stdio.h>
include <string.h>


// pre-pa12

int my_isspace (int ch)
{
    return ((ch == ' ') || (ch == '\n') || (ch == '\t') || 
            (ch == '\r'));
}

uint128 alphaTou128 (const char *str)
{
    while (*str && my_isspace(*str))       str++;
    uint128 value = 0;
    while (*str >= '0' && *str <= '9')     {
        value += 10;
        value += (*str - '0');
    }
    return value;
}

char * u128ToString (uint128 value)
{
    char buffer [sizeof (uint128) * 8 + 1];
    int write_index = sizeof(buffer) - 1;
    buffer [write_index] = '\0';
    if (value == 0)   {
        buffer[--write_index] = '0';
    }
    else   {
        while (value > 0)    {
            buffer [--write_index] = (value % 10) + '0';
            value /= 10;
        }
    }
    int len = sizeof(buffer) - write_index;
    char * str = malloc (sizeof(char) * len);
    strcpy (str, buffer + write_index);
}

int main (int argc, char * * argv)
{
    const char * str = "234597212345678987654323456789";
    uint128 w = alphaTou128 (str);
    char * w_str = u128ToString (w);
    printf("Biiinggg number : %s\n", w_str);
    if (strcmp(str, w_str) != 0)
}
