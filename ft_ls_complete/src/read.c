
#include "../include/ft_ls.h"

void	print_error_path(const char *prefix, const char *name)
{
	write(2, prefix, strlen(prefix));
	write(2, name, strlen(name));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

int		stat_entry(const char *path, const char *name, t_entry *e)
{
	char *full = NULL;
	struct stat sb;
	int ret;

	if (name)
		full = join_path(path, name);
	else
		full = strdup(path);
	if (!full) return -1;
	ret = lstat(full, &sb);
	if (ret != 0)
	{
		print_error_path("ft_ls: ", name ? full : path);
		free(full);
		return -1;
	}
	e->name = strdup(name ? name : path);
	e->path = full;
	e->sb = sb;
	e->is_dir = S_ISDIR(sb.st_mode);
	e->is_link = S_ISLNK(sb.st_mode);
	return 0;
}

int		read_dir(const char *path, const t_flags *flg, t_vec *out)
{
	DIR *d = opendir(path);
	struct dirent *de;
	t_vec v;
	if (!d)
	{
		print_error_path("ft_ls: ", path);
		return -1;
	}
	vec_init(&v);
	while ((de = readdir(d)))
	{
		if (!flg->a && de->d_name[0] == '.')
			continue;
		t_entry e;
		if (stat_entry(path, de->d_name, &e) == 0)
			vec_push(&v, e);
	}
	closedir(d);
	sort_entries(&v, flg);
	*out = v;
	return 0;
}
