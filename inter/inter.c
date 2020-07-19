#include <unistd.h>

int		main(int ac, char **av)
{
	int	i;
	int	j;
	int	k;
	int	doub;
	int	prev;

	if (ac == 3)
	{
		i = -1;
		while (av[1][++i])
		{
			j = -1;
			doub = 0;
			while (av[2][++j])
				if (av[1][i] == av[2][j])
					doub++;
			k = i;
			prev = 0;
			if (doub > 0)
			{
				while (k)
					if (av[1][--k] == av[1][i])
						prev++;
				if (prev == 0)
					write(1, &av[1][i], 1);
			}
		}
	}
	k = 10;
	write(1, &k, 1);
	return (0);
}