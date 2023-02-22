/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_pointoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:46:30 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:44:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*chop_nbr(char *str, t_ull nb, t_ull len, char *base)
{
	while (nb / 16)
	{
		len--;
		str[len] = base[nb % 16];
		nb = nb / 16;
	}
	str[len - 1] = base[nb % 16];
	str[1] = 'x';
	str[0] = '0';
	return (str);
}

static t_ull	ft_getlen(t_ull nb)
{
	t_ull	len;

	len = 1;
	while (nb / 16)
	{
		nb = nb / 16;
		len++;
	}
	return (len);
}

char	*ft_pointoa(t_ull nb)
{
	t_ull	len;
	char	*str;

	len = ft_getlen(nb) + 2;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	return (chop_nbr(str, nb, len, BASELHEX));
}
