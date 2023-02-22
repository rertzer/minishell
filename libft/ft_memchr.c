/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:46 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:14:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*cs;

	if (! s)
		return (NULL);
	cs = (char *)s;
	i = 0;
	while (cs[i] != (unsigned char)c && i < n)
		i++;
	if (i == n)
		return (NULL);
	return (&cs[i]);
}
