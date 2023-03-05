/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:42:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 15:53:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pp_nullfree(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int		pp_path_size(char *s1, char const *s2)
{
	size_t	i;

	i = ft_strlen(s1);
	if (s1[i - 1] == '/')
	{
		s1[i - 1] = '\0';
		i--;
	}
	i += ft_strlen(s2);
	return (i + 2);
}

char	*pp_pathjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	dest = malloc(sizeof(char) *(pp_path_size(s1, s2)));
	if (NULL == dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '/';
	i++;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
