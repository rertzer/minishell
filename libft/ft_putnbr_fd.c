/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:42:27 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:18:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	print_nbr_fd(unsigned int n, int fd)
{
	char	c;

	c = '0' + n;
	write(fd, &c, 1);
}

static void	chop_nbr_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		chop_nbr_fd(n / 10, fd);
		chop_nbr_fd(n % 10, fd);
	}
	else
		print_nbr_fd(n, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = n * -1;
	}
	else
		nb = n;
	chop_nbr_fd(nb, fd);
}
