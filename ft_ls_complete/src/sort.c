
#define _GNU_SOURCE
#include "../include/ft_ls.h"

typedef struct s_sortctx {
	int by_time;
	int reverse;
} t_sortctx;

static int cmp_name(const t_entry *a, const t_entry *b)
{
	return strcmp(a->name, b->name);
}

static int cmp_time_then_name(const t_entry *a, const t_entry *b)
{
	if (a->sb.st_mtime == b->sb.st_mtime)
		return cmp_name(a, b);
	if (a->sb.st_mtime > b->sb.st_mtime) return -1;
	return 1;
}

static int trampoline(const void *aa, const void *bb, void *ctxv)
{
	const t_entry *a = (const t_entry*)aa;
	const t_entry *b = (const t_entry*)bb;
	t_sortctx *ctx = (t_sortctx*)ctxv;
	int c = ctx->by_time ? cmp_time_then_name(a,b) : cmp_name(a,b);
	return ctx->reverse ? -c : c;
}

void	sort_entries(t_vec *vec, const t_flags *flg)
{
	t_sortctx ctx;
	ctx.by_time = flg->t;
	ctx.reverse = flg->r;
#if defined(__GLIBC__) || defined(__APPLE__)
	qsort_r(vec->v, vec->size, sizeof(t_entry), trampoline, &ctx);
#else
	/* Fallback */
	size_t i, j;
	for (i = 0; i + 1 < vec->size; ++i)
		for (j = 0; j + 1 < vec->size - i; ++j)
		{
			if (trampoline(&vec->v[j], &vec->v[j+1], &ctx) > 0)
			{
				t_entry tmp = vec->v[j];
				vec->v[j] = vec->v[j+1];
				vec->v[j+1] = tmp;
			}
		}
#endif
}
