#include <unistd.h>

void    camel(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            write(1, "_", 1);
            str[i] += 32;
        }
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
        camel(argv[1]);
    write(1, "\n", 1);
}