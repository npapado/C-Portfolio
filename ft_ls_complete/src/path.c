
#include "../include/ft_ls.h"

char	*join_path(const char *a, const char *b)
{
	size_t la = strlen(a), lb = strlen(b);
	size_t need = la + (la && a[la-1] != '/' ? 1 : 0) + lb + 1;
	char *s = (char*)malloc(need);
	size_t i = 0, j = 0;
	if (!s) exit(1);
	while (i < la) { s[i] = a[i]; i++; }
	if (i && s[i-1] != '/') s[i++] = '/';
	while (j < lb) { s[i+j] = b[j]; j++; }
	s[i+j] = '\0';
	return s;
}
