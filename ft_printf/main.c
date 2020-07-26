#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *str, ... );

int	main(void)
{
	ft_printf("[%s]\n", "abcd");
	printf("[%s]\n", "abcd");
	ft_printf("[%5s]\n", "abcd");
	printf("[%5s]\n", "abcd");
	ft_printf("[%.2s]\n", "abcd");
	printf("[%.2s]\n", "abcd");
	ft_printf("[%5.2s]\n", "abcd");
	printf("[%5.2s]\n", "abcd");


	ft_printf("\n[%d]\n", INT_MAX);
	printf("[%d]\n", INT_MAX);
	ft_printf("[%20d]\n", INT_MAX);
	printf("[%20d]\n", INT_MAX);
	ft_printf("[%.20d]\n", INT_MAX);
	printf("[%.20d]\n", INT_MAX);
	ft_printf("[%30.20d]\n", INT_MAX);
	printf("[%30.20d]\n", INT_MAX);

	ft_printf("\n[%d]\n", INT_MIN);
	printf("[%d]\n", INT_MIN);
	ft_printf("[%20d]\n", INT_MIN);
	printf("[%20d]\n", INT_MIN);
	ft_printf("[%.20d]\n", INT_MIN);
	printf("[%.20d]\n", INT_MIN);
	ft_printf("[%30.20d]\n", INT_MIN);
	printf("[%30.20d]\n", INT_MIN);
	ft_printf("[%4.d]\n", 0);
	printf("[%4.d]\n", 0);


	ft_printf("\n[%x]\n", 42);
	printf("[%x]\n", 42);
	ft_printf("[%4x]\n", 42);
	printf("[%4x]\n", 42);
	ft_printf("[%.4x]\n", 42);
	printf("[%.4x]\n", 42);
	ft_printf("[%5.4x]\n", 42);
	printf("[%5.4x]\n", 42);
	ft_printf("[%4.x]\n", 0);
	printf("[%4.x]\n", 0);
}
