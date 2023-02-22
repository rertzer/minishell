/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:31:19 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/15 09:09:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strid(const char *big, const char *little)
{
	size_t	i;

	i = 0;
	while (big[i] && big[i] == little[i])
		i++;
	return (little[i]);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		little_len;

	if ((little == NULL) || (little[0] == '\0'))
		return ((char *)big);
	if (len == 0)
		return (NULL);
	little_len = 0;
	while (little[little_len])
		little_len++;
	i = 0;
	while ((big[i]) && (i < len - little_len + 1))
	{
		if (ft_strid(&big[i], little) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
