#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (i < n)
	{
		a = (unsigned char)s1[i];
		b = (unsigned char)s2[i];
		if (a != b || a == '\0' || b == '\0')
			return ((int)(a - b));
		i++;
	}
	return (0);
}
