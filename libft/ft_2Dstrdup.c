/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2Dstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:47:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:00:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2Dstrdup(char **src)
{
	char	**dest;
	int		i;
	int		size;

	size = -1;
	while (src[++size])
		size++;
	dest = malloc(sizeof(char *) * (size + 1));
	if (NULL ==  dest)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
			return (ft_split_flush(dest));
	}
	dest[i] = NULL;
	return (dest);
}
