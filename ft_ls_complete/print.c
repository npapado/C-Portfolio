#include "ft_ls.h"

static void perms_str(mode_t m, char *out)
{
	out[0] = S_ISDIR(m) ? 'd' : S_ISLNK(m) ? 'l' : S_ISCHR(m) ? 'c' :
	         S_ISBLK(m) ? 'b' : S_ISFIFO(m) ? 'p' : S_ISSOCK(m) ? 's' : '-';
	const char rwx[] = {'r','w','x'};
	for (int i = 0; i < 9; ++i)
		out[1+i] = (m & (1 << (8 - i))) ? rwx[i%3] : '-';
	if (m & S_ISUID) out[3] = (out[3] == 'x') ? 's' : 'S';
	if (m & S_ISGID) out[6] = (out[6] == 'x') ? 's' : 'S';
	if (m & S_ISVTX) out[9] = (out[9] == 'x') ? 't' : 'T';
	out[10] = '\0';
}

static void time_str(time_t t, char *buf, size_t bufsz)
{
	time_t now = time(NULL);
	struct tm tm;
	localtime_r(&t, &tm);
	if (now - t > 15552000 || t - now > 15552000)
		strftime(buf, bufsz, "%b %e  %Y", &tm);
	else
		strftime(buf, bufsz, "%b %e %H:%M", &tm);
}

void print_error_path(const char *path)
{
	fprintf(stderr, "ft_ls: %s: %s\n", path, strerror(errno));
}

static void print_long(const t_entry *e)
{
	char perms[11]; perms_str(e->st.st_mode, perms);
	struct passwd *pw = getpwuid(e->st.st_uid);
	struct group  *gr = getgrgid(e->st.st_gid);
	char tbuf[64]; time_str(e->st.st_mtime, tbuf, sizeof(tbuf));

	if (S_ISCHR(e->st.st_mode) || S_ISBLK(e->st.st_mode))
		printf("%s %2lu %-8s %-8s %3u, %3u %s %s",
			perms, (unsigned long)e->st.st_nlink,
			pw ? pw->pw_name : "UNKNOWN",
			gr ? gr->gr_name : "UNKNOWN",
			(unsigned)(major(e->st.st_rdev)), (unsigned)(minor(e->st.st_rdev)),
			tbuf, e->name);
	else
		printf("%s %2lu %-8s %-8s %8lld %s %s",
			perms, (unsigned long)e->st.st_nlink,
			pw ? pw->pw_name : "UNKNOWN",
			gr ? gr->gr_name : "UNKNOWN",
			(long long)e->st.st_size, tbuf, e->name);

	if (e->is_link)
	{
		char buf[PATH_MAX]; ssize_t n = readlink(e->path, buf, sizeof(buf)-1);
		if (n >= 0) { buf[n] = 0; printf(" -> %s", buf); }
	}
	putchar('\n');
}

void print_entries(const char *header, const t_vec *v, const t_opts *o, int print_header)
{
	if (print_header && header && *header)
		printf("%s:\n", header);

	if (o->l)
	{
		for (size_t i = 0; i < v->len; ++i) print_long(&v->data[i]);
	}
	else
	{
		for (size_t i = 0; i < v->len; ++i)
			printf("%s\n", v->data[i].name);
	}
}
