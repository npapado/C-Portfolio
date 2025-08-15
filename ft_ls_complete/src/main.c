
#include "../include/ft_ls.h"

static void usage(void)
{
	write(2, "usage: ft_ls [-lRart] [file ...]\n", 34);
}

static void handle_path(const char *path, const t_flags *flg, int multi);

static void list_dir_recursive(const char *path, const t_flags *flg, int multi)
{
	t_vec entries;
	size_t i;

	if (!path) return;
	if (read_dir(path, flg, &entries) != 0)
		return;
	print_entries(&entries, multi ? path : NULL, flg);
	if (flg->R)
	{
		for (i = 0; i < entries.size; ++i)
		{
			t_entry *e = &entries.v[i];
			if (e->is_dir && strcmp(e->name, ".") && strcmp(e->name, ".."))
				list_dir_recursive(e->path, flg, 1);
		}
	}
	vec_free(&entries);
}

static void handle_path(const char *path, const t_flags *flg, int multi)
{
	t_entry e;
	if (stat_entry(path, NULL, &e) != 0)
		return;
	if (!e.is_dir || (e.is_link && flg->l))
	{
		t_vec v; vec_init(&v); vec_push(&v, e);
		print_entries(&v, multi ? NULL : NULL, flg);
		vec_free(&v);
	}
	else
	{
		list_dir_recursive(path, flg, multi);
		free(e.name); free(e.path);
	}
}

int main(int ac, char **av)
{
	t_flags flg = {0,0,0,0,0};
	int i, first;
	t_vec files = {0};
	t_vec dirs = {0};
	int had_args = 0;

	parse_flags(ac, av, &flg, &first);
	vec_init(&files); vec_init(&dirs);

	if (first >= ac)
	{
		list_dir_recursive(".", &flg, 0);
		vec_free(&files); vec_free(&dirs);
		return 0;
	}

	for (i = first; i < ac; ++i)
	{
		t_entry e;
		if (stat_entry(av[i], NULL, &e) != 0) continue;
		had_args = 1;
		if (e.is_dir && !(e.is_link && flg.l))
			vec_push(&dirs, e);
		else
			vec_push(&files, e);
	}

	if (files.size)
	{
		sort_entries(&files, &flg);
		print_entries(&files, NULL, &flg);
	}
	if (dirs.size && files.size)
		write(1, "\n", 1);
	if (dirs.size)
	{
		size_t d;
		sort_entries(&dirs, &flg);
		for (d = 0; d < dirs.size; ++d)
		{
			if (had_args)
			{
				write(1, dirs.v[d].path, strlen(dirs.v[d].path));
				write(1, ":\n", 2);
			}
			list_dir_recursive(dirs.v[d].path, &flg, 1);
			if (d + 1 < dirs.size) write(1, "\n", 1);
		}
	}
	vec_free(&files); vec_free(&dirs);
	return 0;
}
