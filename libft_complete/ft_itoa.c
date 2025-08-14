#include "libft.h"

static size_t	int_len(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	len;
	char	*str;

	nb = (long)n;
	len = int_len(nb);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[len - 1] = '0';
	while (nb > 0)
	{
		str[len - 1] = (char)('0' + (nb % 10));
		nb /= 10;
		len--;
	}
	return (str);
}
