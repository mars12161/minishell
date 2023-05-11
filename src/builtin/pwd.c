#include "builtin.h"

int ft_pwd(void)
{
    static char pwd[PATH_SIZE];

    if (getcwd(pwd, PATH_SIZE))
    {
        printf("%s", pwd);
        return (0);
    }
    else
        return (-1);
}