
#include "../include/ft_ls.h"

static void mode_to_str(mode_t m, char out[11])
{
	out[0] = S_ISDIR(m) ? 'd' : S_ISLNK(m) ? 'l' : S_ISCHR(m) ? 'c' :
	         S_ISBLK(m) ? 'b' : S_ISSOCK(m) ? 's' : S_ISFIFO(m) ? 'p' : '-';
	out[1] = (m & S_IRUSR) ? 'r' : '-';
	out[2] = (m & S_IWUSR) ? 'w' : '-';
	out[3] = (m & S_IXUSR) ? ((m & S_ISUID) ? 's' : 'x') : ((m & S_ISUID) ? 'S' : '-');
	out[4] = (m & S_IRGRP) ? 'r' : '-';
	out[5] = (m & S_IWGRP) ? 'w' : '-';
	out[6] = (m & S_IXGRP) ? ((m & S_ISGID) ? 's' : 'x') : ((m & S_ISGID) ? 'S' : '-');
	out[7] = (m & S_IROTH) ? 'r' : '-';
	out[8] = (m & S_IWOTH) ? 'w' : '-';
	out[9] = (m & S_IXOTH) ? ((m & S_ISVTX) ? 't' : 'x') : ((m & S_ISVTX) ? 'T' : '-');
	out[10] = '\0';
}

static void fmt_time(time_t t, char *buf, size_t n)
{
	time_t now = time(NULL);
	struct tm *tmv = localtime(&t);
	char tmp[64];
	if (!tmv) { snprintf(buf, n, "????????????"); return; }
	strftime(tmp, sizeof(tmp), "%b %e %H:%M", tmv);
	if (t > now + 15778463 || t < now - 15778463) /* ~6 months */
		strftime(tmp, sizeof(tmp), "%b %e  %Y", tmv);
	snprintf(buf, n, "%s", tmp);
}

static void widths_calc(const t_vec *v, int widths[3])
{
	size_t i;
	int w_link = 0, w_size = 0;
	char num[32];
	for (i = 0; i < v->size; ++i)
	{
		const t_entry *e = &v->v[i];
		snprintf(num, sizeof(num), "%lu", (unsigned long)e->sb.st_nlink);
		if ((int)strlen(num) > w_link) w_link = strlen(num);
		snprintf(num, sizeof(num), "%lld", (long long)e->sb.st_size);
		if ((int)strlen(num) > w_size) w_size = strlen(num);
	}
	widths[0] = w_link; widths[1] = 0; widths[2] = w_size;
}

void	print_long(const t_entry *e, int widths[3])
{
	char mode[11], tbuf[32];
	struct passwd *pw;
	struct group *gr;
	char linkbuf[PATH_MAX + 1];
	ssize_t lr;

	mode_to_str(e->sb.st_mode, mode);
	fmt_time(e->sb.st_mtime, tbuf, sizeof(tbuf));

	pw = getpwuid(e->sb.st_uid);
	gr = getgrgid(e->sb.st_gid);

	dprintf(1, "%s %*lu %s  %s %*lld %s %s",
		mode,
		widths[0], (unsigned long)e->sb.st_nlink,
		pw ? pw->pw_name : "?", gr ? gr->gr_name : "?",
		widths[2], (long long)e->sb.st_size,
		tbuf, e->name);
	if (S_ISLNK(e->sb.st_mode))
	{
		lr = readlink(e->path, linkbuf, PATH_MAX);
		if (lr >= 0) { linkbuf[lr] = '\0'; dprintf(1, " -> %s", linkbuf); }
	}
	dprintf(1, "\n");
}

void	print_entries(t_vec *vec, const char *header, const t_flags *flg)
{
	size_t i;
	if (header)
	{
		write(1, header, strlen(header));
		write(1, ":\n", 2);
	}
	if (!flg->l)
	{
		for (i = 0; i < vec->size; ++i)
		{
			write(1, vec->v[i].name, strlen(vec->v[i].name));
			write(1, "\n", 1);
		}
	}
	else
	{
		int widths[3] = {0,0,0};
		widths_calc(vec, widths);
		for (i = 0; i < vec->size; ++i)
			print_long(&vec->v[i], widths);
	}
}
