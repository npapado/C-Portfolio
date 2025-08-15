#include "ft_ls.h"

int ls_path(const char *path, const t_opts *o, int print_header)
{
	t_vec v; vec_init(&v);
	if (collect_dir(path, o, &v) != 0)
	{
		print_error_path(path);
		return -1;
	}
	sort_entries(&v, o);
	print_entries(path, &v, o, print_header);

	if (o->R)
	{
		for (size_t i = 0; i < v.len; ++i)
		{
			t_entry *e = &v.data[i];
			if (e->is_dir)
			{
				if (strcmp(e->name, ".") == 0 || strcmp(e->name, "..") == 0) continue;
				printf("\n%s:\n", e->path);
				ls_path(e->path, o, 0);
			}
		}
	}
	vec_free(&v);
	return 0;
}
