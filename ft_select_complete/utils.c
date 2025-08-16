
#include "ft_select.h"
#include <string.h>

void *xmalloc(size_t n)
{
    void *p = malloc(n);
    if (!p) { write(2, "ft_select: malloc failed\n", 25); _exit(1); }
    return p;
}

char *xstrdup(const char *s)
{
    size_t len = 0;
    char *p;
    if (!s) return NULL;
    while (s[len]) len++;
    p = xmalloc(len + 1);
    for (size_t i = 0; i < len; ++i) p[i] = s[i];
    p[len] = '\0';
    return p;
}
