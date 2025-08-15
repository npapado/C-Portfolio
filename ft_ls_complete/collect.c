#include "ft_ls.h"

int stat_path(const char *path, t_entry *e)
{
	struct stat st;
	if (lstat(path, &st) != 0) return -1;
	memset(e, 0, sizeof(*e));
	e->path = strdup(path);
	const char *slash = strrchr(path, '/');
	e->name = strdup(slash ? slash + 1 : path);
	e->st = st;
	e->is_dir = S_ISDIR(st.st_mode);
	e->is_link = S_ISLNK(st.st_mode);
	return 0;
}

int collect_dir(const char *path, const t_opts *o, t_vec *out)
{
	DIR *dir = opendir(path);
	if (!dir) return -1;
	struct dirent *de;
	while ((de = readdir(dir)) != NULL)
	{
		if (!o->a && de->d_name[0] == '.')
			continue;
		size_t plen = strlen(path);
		size_t dlen = strlen(de->d_name);
		int need_slash = (plen > 0 && path[plen-1] != '/');
		char *full = (char*)malloc(plen + need_slash + dlen + 1);
		if (!full) { closedir(dir); return -1; }
		strcpy(full, path);
		if (need_slash) strcat(full, "/");
		strcat(full, de->d_name);
		t_entry e;
		if (stat_path(full, &e) == 0)
		{
			free(e.path);
			e.path = full;
			free(e.name);
			e.name = strdup(de->d_name);
			vec_push(out, e);
		}
		else
		{
			free(full);
		}
	}
	closedir(dir);
	return 0;
}
