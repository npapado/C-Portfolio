#include "libft.h"

static void	putnbr_rec(long n, int fd)
{
	char	c;

	if (n >= 10)
		putnbr_rec(n / 10, fd);
	c = (char)('0' + (n % 10));
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	putnbr_rec(nb, fd);
}
