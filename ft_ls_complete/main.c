#include "ft_ls.h"

static void split_args(char **paths, int n, t_vec *files, t_vec *dirs, t_vec *errs)
{
	for (int i = 0; i < n; ++i)
	{
		t_entry e;
		if (stat_path(paths[i], &e) != 0)
		{
			t_entry er = {0};
			er.name = strdup(paths[i]);
			er.path = strdup(paths[i]);
			vec_push(errs, er);
			continue;
		}
		if (e.is_dir) vec_push(dirs, e);
		else vec_push(files, e);
	}
}

static void print_errors(const t_vec *errs)
{
	for (size_t i = 0; i < errs->len; ++i)
	{
		errno = ENOENT;
		print_error_path(errs->data[i].path);
	}
}

int main(int argc, char **argv)
{
	t_opts o; char **paths; int npaths;
	if (parse_args(argc, argv, &o, &paths, &npaths) != 0) return 1;

	if (npaths == 0) { char *def[] = { "." }; paths = def; npaths = 1; }

	t_vec files, dirs, errs; vec_init(&files); vec_init(&dirs); vec_init(&errs);
	split_args(paths, npaths, &files, &dirs, &errs);

	sort_entries(&files, &o);
	sort_entries(&dirs, &o);

	print_errors(&errs);

	if (files.len > 0)
	{
		print_entries("", &files, &o, 0);
		if (dirs.len > 0) putchar('\n');
	}

	for (size_t i = 0; i < dirs.len; ++i)
	{
		const char *hdr = (npaths > 1 || dirs.len > 1 || files.len > 0) ? dirs.data[i].path : NULL;
		if (hdr) printf("%s:\n", hdr);
		ls_path(dirs.data[i].path, &o, 0);
		if (i + 1 < dirs.len) putchar('\n');
	}

	vec_free(&files); vec_free(&dirs); vec_free(&errs);
	return 0;
}
