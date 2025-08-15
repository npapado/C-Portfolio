#include "ft_ls.h"

void vec_init(t_vec *v) { v->data = NULL; v->len = 0; v->cap = 0; }

void vec_push(t_vec *v, t_entry e)
{
	if (v->len == v->cap)
	{
		size_t ncap = v->cap ? v->cap * 2 : 16;
		t_entry *n = (t_entry*)realloc(v->data, ncap * sizeof(t_entry));
		if (!n) { perror("ft_ls: realloc"); exit(1); }
		v->data = n; v->cap = ncap;
	}
	v->data[v->len++] = e;
}

void vec_free(t_vec *v)
{
	for (size_t i = 0; i < v->len; ++i)
	{
		free(v->data[i].name);
		free(v->data[i].path);
	}
	free(v->data);
	v->data = NULL; v->len = v->cap = 0;
}
