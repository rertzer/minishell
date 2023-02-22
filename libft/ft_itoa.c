/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:15:31 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:11:21 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*chop_nbr(char *str, unsigned int nb, int sign, unsigned int len)
{
	while (nb / 10)
	{
		len--;
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	str[len - 1] = (nb % 10) + '0';
	if (sign < 0)
		str[len - 2] = '-';
	return (str);
}

static unsigned int	ft_getlen(unsigned int nb, int sign)
{
	unsigned int	len;

	len = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		len++;
	}
	if (sign < 0)
		len++;
	return (len);
}

char	*ft_itoa(int nb)
{
	unsigned int	bignum;
	unsigned int	len;
	int				sign;
	char			*str;

	sign = 1;
	if (nb < 0)
		sign = -1;
	bignum = nb * sign;
	len = ft_getlen(bignum, sign);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	return (chop_nbr(str, bignum, sign, len));
}
