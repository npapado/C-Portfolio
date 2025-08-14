#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	size_t	outlen;
	char	*out;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		outlen = 0;
	else if (len > slen - start)
		outlen = slen - start;
	else
		outlen = len;
	out = (char *)malloc(outlen + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < outlen)
	{
		out[i] = s[start + i];
		i++;
	}
	out[outlen] = '\0';
	return (out);
}
