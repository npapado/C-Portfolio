
#include "../include/ft_ls.h"

void	vec_init(t_vec *vec)
{
	vec->v = NULL; vec->size = 0; vec->cap = 0;
}

void	vec_push(t_vec *vec, t_entry e)
{
	if (vec->size == vec->cap)
	{
		size_t ncap = vec->cap ? vec->cap * 2 : 16;
		t_entry *nv = (t_entry*)malloc(ncap * sizeof(t_entry));
		if (!nv) exit(1);
		if (vec->v) memcpy(nv, vec->v, vec->size * sizeof(t_entry));
		free(vec->v);
		vec->v = nv; vec->cap = ncap;
	}
	vec->v[vec->size++] = e;
}

void	vec_free(t_vec *vec)
{
	size_t i;
	for (i = 0; i < vec->size; ++i)
	{
		free(vec->v[i].name);
		free(vec->v[i].path);
	}
	free(vec->v);
	vec->v = NULL; vec->size = vec->cap = 0;
}
