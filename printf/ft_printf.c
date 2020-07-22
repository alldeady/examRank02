#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int g_return;
int g_width;
int g_dot;

static void	ft_putchar(int c)
{
	write(1, &c, 1);
	g_return++;
}

static void	ft_putstr(char *str, int len)
{
	while (*str && len--)
	{
		ft_putchar(*str);
		str++;
	}
}

static int	ft_strlen(char *str)
{
	int	len = 0;

	while (*str++)
		len++;
	return (len);
}

static void	ft_print_s(char *str)
{
	int		len = ft_strlen(str);

	if (g_dot >= 0 && len < g_dot)
		g_dot = len;
	if (g_dot >= 0)
		while (g_width - g_dot > 0)
			{ft_putchar(' '); g_width--;}
	else
		while (g_width - len > 0)
			{ft_putchar(' '); g_width--;}
	if (g_dot >= 0)
	{
		while (g_dot - len > 0)
			{ft_putchar(' '); g_dot--;}
		ft_putstr(str, g_dot);
	}
	else
		ft_putstr(str, len);
}

static char	*ft_itoa(long nbr, int base)
{
	char	*ret;
	long	nbr_tmp = nbr;
	int		len = 0;

	if (nbr == 0)
		len = 1;
	while (nbr_tmp)
	{
		nbr_tmp /= base;
		len++;
	}
	if (nbr < 0)
		len++;
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = '\0';

	if (nbr < 0)
		{nbr *= -1; ret[0] = '-';}
	while (len)
	{
		ret[len - 1] = (nbr % base) + (nbr % base > 9 ? 55 + 32 : 48);
		nbr /= base;
		len--;
	}
	return (ret);
}

static void	ft_print_x(unsigned int nbr)
{
	char	*str;
	int		len = 0;

	str = ft_itoa(nbr, 16);
	len = ft_strlen(str);
	if (g_dot >= 0 && nbr == 0)
		while (g_width > 0)
			{ft_putchar(' '); g_width--;}
	if (g_dot >= 0 && len > g_dot)
		g_dot = len;
	if (g_dot >= 0)
		while (g_width - g_dot > 0)
			{ft_putchar(' '); g_width--;}
	else
		while (g_width - len > 0)
			{ft_putchar(' '); g_width--;}
	if (g_dot >= 0)
		while (g_dot - len > 0)
			{ft_putchar('0'); g_dot--;}
	ft_putstr(str, g_dot);
	free(str);
}

static void	ft_print_d(int nbr)
{
	char	*str;
	int		len = 0;
	int		nbr_tmp = nbr;

	if (g_dot >= 0 && nbr == 0)
		while (g_width > 0)
			{ft_putchar(' '); g_width--;}
	if (g_dot >= 0 && nbr < 0)
		{nbr *= -1; g_width--;}
	str = ft_itoa(nbr, 10);
	len = ft_strlen(str);
	if (g_dot >= 0 && len > g_dot)
		g_dot = len;
	if (g_dot >= 0)
		while (g_width - g_dot > 0)
			{ft_putchar(' '); g_width--;}
	else
		while (g_width - len > 0)
			{ft_putchar(' '); g_width--;}
	if (g_dot >= 0 && nbr_tmp < 0)
		ft_putchar('-');
	if (g_dot >= 0)
		while (g_dot - len > 0)
			{ft_putchar('0'); g_dot--;}
	ft_putstr(str, g_dot);
	free(str);
}

static void	ft_spreader(int c, va_list av)
{
	if (c == 's')
		ft_print_s(va_arg(av, char *));
	else if (c == 'd')
		ft_print_d(va_arg(av, int));
	else if (c == 'x')
		ft_print_x(va_arg(av, unsigned int));
}

static int	ft_dot(char *str, int i)
{
	g_dot++;
	i++;
	while (str[i] >= '0' && str[i] <= '9')
		g_dot = (g_dot * 10) + str[i++] - 48;
	return (i);
}

static int	ft_width(char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
		g_width = (g_width * 10) + str[i++] - 48;
	return (i);
}

static int	ft_check_type(int c)
{
	return (c == 's' || c == 'd' || c == 'x');
}

static int	ft_flag_scan(char *str, int i)
{
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i = ft_width(str, i);
		if (str[i] == '.')
			i = ft_dot(str, i);
		if (ft_check_type(str[i]))
			break ;
	}
	return (i);
}

static void ft_check(char *str, va_list av)
{
	int	i = -1;

	while (str[++i])
	{
		g_width = 0;
		g_dot = -1;
		if (str[i] == '%' && str[i + 1])
		{
			i = ft_flag_scan(str, i);
			if (ft_check_type(str[i]))
				ft_spreader(str[i], av);
			else if (str[i])
				ft_putchar(str[i]);
		}
		else if (str[i] != '%')
			ft_putchar(str[i]);
	}
}

int			ft_printf(char *str, ...)
{
	va_list	av;

	g_return = 0;
	va_start(av, str);
	ft_check(str, av);
	va_end(av);
	return (g_return);
}

int 	main(void)
{
    int res_1;
    int res_2;

//STR
    res_2 = printf("%10.2s\n", "toto");
    res_1 = ft_printf("%10.2s\n", "toto");
    if (res_1 != res_2)
        printf("1)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2.2s\n", "toto");
    res_1 = ft_printf("%2.2s\n", "toto");
    if (res_1 != res_2)
        printf("2)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2.20s\n", "toto");
    res_1 = ft_printf("%2.20s\n", "toto");
    if (res_1 != res_2)
        printf("3)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%20.20s\n", "toto");
    res_1 = ft_printf("%20.20s\n", "toto");
    if (res_1 != res_2)
        printf("4)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%.2s\n", "toto");
    res_1 = ft_printf("%.2s\n", "toto");
    if (res_1 != res_2)
        printf("5)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%.20s\n", "toto");
    res_1 = ft_printf("%.20s\n", "toto");
    if (res_1 != res_2)
        printf("6)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%12s\n", "toto");
    res_1 = ft_printf("%12s\n", "toto");
    if (res_1 != res_2)
        printf("7)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2s\n", "toto");
    res_1 = ft_printf("%2s\n", "toto");
    if (res_1 != res_2)
        printf("8)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%s\n", "toto");
    res_1 = ft_printf("%s\n", "toto");
    if (res_1 != res_2)
        printf("9)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

//INT
    res_1 = ft_printf("Magic %s is %15d\n", "number", 42);
    res_2 = printf("Magic %s is %15d\n", "number", 42);
    if (res_1 != res_2)
        printf("1)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %1d\n", "number", 42);
    res_2 = printf("Magic %s is %1d\n", "number", 42);
    if (res_1 != res_2)
        printf("2)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_1 = ft_printf("Magic %s is %15.2d\n", "number", 42);
    res_2 = printf("Magic %s is %15.2d\n", "number", 42);
    if (res_1 != res_2)
        printf("3)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %15.20d\n", "number", -42);
    res_2 = printf("Magic %s is %15.20d\n", "number", -42);
    if (res_1 != res_2)
        printf("4)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_1 = ft_printf("Magic %s is %.20d\n", "number", -42);
    res_2 = printf("Magic %s is %.20d\n", "number", -42);
    if (res_1 != res_2)
        printf("5)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %.2d\n", "number", 42);
    res_2 = printf("Magic %s is %.2d\n", "number", 42);
    if (res_1 != res_2)
        printf("6)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %d\n", "number", 42);
    res_2 = printf("Magic %s is %d\n", "number", 42);
    if (res_1 != res_2)
        printf("7)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

// HEX
    res_1 = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %x\n", 42, 42);
    if (res_1 != res_2)
        printf("1)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %20x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %20x\n", 42, 42);
    if (res_1 != res_2)
        printf("2)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %1x\n", 42, 42);
    if (res_1 != res_2)
        printf("3)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %1.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %1.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("4)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %10.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %10.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("5)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

     res_1 = ft_printf("Hexadecimal for %d is %.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("6)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

      res_1 = ft_printf("Hexadecimal for %d is %.10x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %.10x\n", 42, 42);
    if (res_1 != res_2)
        printf("7)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

       res_1 = ft_printf("%.2x\n", 0);
   	   res_2 = printf("%.2x\n", 0);
    if (res_1 != res_2)
        printf("8)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);
}
