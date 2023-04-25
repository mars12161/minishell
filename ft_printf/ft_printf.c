/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:22 by yli               #+#    #+#             */
/*   Updated: 2023/04/18 11:13:23 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void    ft_putchar(char c, int *len)
{
    write(1, &c, 1);
    *len += 1;
}

void    ft_putstr(char *str, int *len)
{
    long unsigned int i;

    i = 0;
    if (!str)
        ft_putstr("(null)", len);
    else
    {
        while (str[i])
        {
            ft_putchar(str[i], len);
            i++;
        }
    }
}

void    ft_putnum(int i, int *len)
{
    if (i == -2147483648)
    {
        write(1, "-2147483648", 11);
        *len += 11;
        return ;
    }
    else if (i < 0)
    {
        ft_putchar('-', len);
        ft_putnum(i * -1, len);
    }
    if (i >= 0 && i <= 9)
        ft_putchar(i + '0', len);
    if (i > 9)
    {
        ft_putnum(i / 10, len);
        ft_putchar(i % 10 + '0', len);
    }
}

void    ft_puthex(unsigned int num, int *len)
{
    char hex[] = "0123456789abcdef";
    char str[50];
    int i;

    i = 0;
    if (num == 0)
    {
        ft_putchar('0', len);
        return ;
    }
    while(num)
    {
        str[i] = hex[num % 16];
        num /= 16;
        i++;
    }
    while(i--)
        ft_putchar(str[i], len);
}

void    checker(char c, va_list *args, int *len, int *i)
{
    if (c == 's')
        ft_putstr(va_arg(*args, char *), len);
    else if (c == 'd')
        ft_putnum(va_arg(*args, int), len);
    else if (c == 'x')
        ft_puthex(va_arg(*args, unsigned int), len);
    else 
        (*i)--;
}


int ft_printf(const char *str, ... )
{
    va_list args;
    int i;
    int len;

    if (!str)
        return (-1);
    i = 0;
    len = 0;
    va_start(args, str);
    while(str[i])
    {
        if (str[i] == '%')
        {
            i += 1;
            checker(str[i], &args, &len, &i);
            i++;
        }
        else
        {
            ft_putchar((char)str[i], &len);
            i++;
        }
    }
    va_end(args);
    return (len);
}

#include <limits.h>
int main()
{
    int i = -2147483648;
    char str[] = "aacc";
    unsigned int x = 15;
    ft_printf("hello %d %s %x\n", i, str, x);
    ft_printf("%d\n", ft_printf("%s\n", str));
    ft_printf("max %d\n", INT_MAX);
	ft_printf("max %d\n", INT_MIN);
    ft_printf("%s\n", "toto");
	printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 42);
	printf("Magic %s is %d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("Hexadecimal for %d is %x\n", 42, 42);
    ft_printf("%x\n", (int)-2147483648);
    printf("%x\n", (int)-2147483648);
}

