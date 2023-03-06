/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:35:45 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:36:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dstrdup(char **src)
{
	char	**dest;
	int		i;
	int		size;

	size = -1;
	while (src[++size])
		size++;
	dest = malloc(sizeof(char *) * (size + 1));
	if (NULL == dest)
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
