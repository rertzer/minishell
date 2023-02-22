/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:42:12 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/15 09:10:21 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_movel(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

static void	*ft_mover(char *dest, const char *src, size_t n)
{
	while (n)
	{
		n--;
		dest[n] = src[n];
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!(dest && src))
		return (dest);
	if (dest > src)
		return (ft_mover((char *)dest, (char *)src, n));
	else
		return (ft_movel((char *)dest, (char *)src, n));
}
