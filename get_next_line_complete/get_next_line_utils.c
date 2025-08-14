
#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\n' && s[i] == '\0')
		return (NULL);
	if (ch == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*gnl_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (!s1)
		return (NULL);
	len = gnl_strlen(s1);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	size_t	outlen;
	char	*out;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
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

char	*gnl_strjoin_free(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*out;

	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	out = (char *)malloc(len1 + len2 + 1);
	if (!out)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < len1)
	{
		out[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		out[len1 + i] = s2[i];
		i++;
	}
	out[len1 + len2] = '\0';
	free(s1);
	return (out);
}
