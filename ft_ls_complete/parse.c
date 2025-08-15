#include "ft_ls.h"

static void usage(void)
{
	fprintf(stderr, "usage: ft_ls [-lRat] [file ...]\n");
}

int parse_args(int argc, char **argv, t_opts *o, char ***paths_out, int *npaths)
{
	int i = 1;
	memset(o, 0, sizeof(*o));
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (strcmp(argv[i], "--") == 0) { i++; break; }
		for (int j = 1; argv[i][j]; ++j)
		{
			char c = argv[i][j];
			if (c == 'l') o->l = 1;
			else if (c == 'R') o->R = 1;
			else if (c == 'a') o->a = 1;
			else if (c == 'r') o->r = 1;
			else if (c == 't') o->t = 1;
			else { usage(); return -1; }
		}
		i++;
	}
	*paths_out = (i < argc) ? &argv[i] : NULL;
	*npaths = (i < argc) ? (argc - i) : 0;
	return 0;
}
