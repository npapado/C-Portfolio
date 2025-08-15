#include "ft_ls.h"

static int cmp_name(const t_entry *a, const t_entry *b)
{
	return strcmp(a->name, b->name);
}

static int cmp_mtime(const t_entry *a, const t_entry *b)
{
	if (a->st.st_mtime != b->st.st_mtime)
		return (a->st.st_mtime > b->st.st_mtime) ? -1 : 1;
	/* Tie-breaker by name ascending */
	return strcmp(a->name, b->name);
}

static void swap(t_entry *a, t_entry *b) { t_entry t = *a; *a = *b; *b = t; }

void sort_entries(t_vec *v, const t_opts *o)
{
	for (size_t i = 0; i < v->len; ++i)
		for (size_t j = 0; j + 1 < v->len - i; ++j)
		{
			int c = o->t ? cmp_mtime(&v->data[j], &v->data[j+1])
						 : cmp_name(&v->data[j], &v->data[j+1]);
			if (o->r) c = -c;
			if (c > 0) swap(&v->data[j], &v->data[j+1]);
		}
}
