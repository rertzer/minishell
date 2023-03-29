/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_uxiota.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:56:32 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:46:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*chop_nbr_base(char *str, t_uint nb, t_uint len, char *base)
{
	t_uint	baselen;

	baselen = ft_strlen(base);
	while (nb / baselen)
	{
		len--;
		str[len] = base[nb % baselen];
		nb = nb / baselen;
	}
	str[len - 1] = base[nb % baselen];
	return (str);
}

static t_uint	ft_getlen_base(t_uint nb, char *base)
{
	t_uint	len;
	t_uint	baselen;

	len = 1;
	baselen = ft_strlen(base);
	while (nb / baselen)
	{
		nb = nb / baselen;
		len++;
	}
	return (len);
}

char	*ft_uxitoa(t_uint nb, char *base)
{
	t_uint	len;
	char	*str;

	len = ft_getlen_base(nb, base);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	return (chop_nbr_base(str, nb, len, base));
}
