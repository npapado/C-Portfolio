
#include "../include/ft_ls.h"

void	parse_flags(int ac, char **av, t_flags *flg, int *first_non_flag)
{
	int i, j;
	for (i = 1; i < ac; ++i)
	{
		if (av[i][0] != '-' || av[i][1] == '\0' || strcmp(av[i], "--") == 0)
			break;
		for (j = 1; av[i][j]; ++j)
		{
			char c = av[i][j];
			if (c == 'l') flg->l = 1;
			else if (c == 'R') flg->R = 1;
			else if (c == 'a') flg->a = 1;
			else if (c == 'r') flg->r = 1;
			else if (c == 't') flg->t = 1;
			else
			{
				write(2, "ft_ls: illegal option -- ", 25);
				write(2, &c, 1);
				write(2, "\n", 1);
				write(2, "usage: ft_ls [-lRart] [file ...]\n", 34);
				exit(1);
			}
		}
	}
	*first_non_flag = i;
	if (i < ac && strcmp(av[i], "--") == 0)
		*first_non_flag = i + 1;
}
