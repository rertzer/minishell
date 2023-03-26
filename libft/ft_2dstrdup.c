/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:35:45 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/23 18:21:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	**ft_2dstrdup(char **src)
{
	char	**dest;
	int		i;
	int		size;
///////////////////////////////////////////////////////////////////////
	size = -1;
	while (src[++size])
		size++;
	fprintf(stderr, "size is %d\n", size);
	dest = malloc(sizeof(char *) * (size + 1));
	if (NULL == dest)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		fprintf(stderr, "%d : %s\n", i, src[i]);
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			fprintf(stderr, "NULLLLLLLLLLLLL\n");
			return (ft_split_flush(dest));
		}
	}
	fprintf(stderr, "proper end\n");
	dest[i] = NULL;
	return (dest);
}
