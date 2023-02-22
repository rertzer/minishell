/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:23:41 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:14:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*cs1;
	const unsigned char		*cs2;

	if (n == 0)
		return (0);
	cs1 = s1;
	cs2 = s2;
	i = 0;
	while (cs1[i] == cs2[i] && i < n - 1)
		i++;
	return (cs1[i] - cs2[i]);
}
