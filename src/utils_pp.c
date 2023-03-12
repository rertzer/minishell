/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:15:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 16:22:35 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pp_nullfree(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int	pp_path_size(char const *s1, char const *s2)
{
	size_t	i;

	i = ft_strlen(s1);
	i += ft_strlen(s2);
	return (i + 1);
}

char	*pp_pathjoin(char const *s1, char const *s2)
{
	size_t	shift;
	char	*dest;

	errno = 0;
	dest = malloc(sizeof(char) *(pp_path_size(s1, s2) + 1));
	if (NULL == dest)
	{
		ms_return_error(errno, R_MAL);
		return (NULL);
	}
	shift = pp_duplicate(s1, dest, 0);
	dest[shift] = '/';
	shift++;
	shift += pp_duplicate(s2, dest, shift);
	dest[shift] = '\0';
	return (dest);
}

int	pp_duplicate(char const *src, char *dest, int shift)
{
	int	i;

	i = 0;
	if (src)
	{
		while (src[i])
		{
			dest[i + shift] = src[i];
			i++;
		}
	}
	return (i);
}
