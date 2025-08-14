#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*p;
	size_t	i;

	if (count != 0 && size != 0 && count > (size_t)-1 / size)
		return (NULL);
	total = count * size;
	p = malloc(total);
	if (!p)
		return (NULL);
	i = 0;
	while (i < total)
	{
		((unsigned char *)p)[i] = 0;
		i++;
	}
	return (p);
}
