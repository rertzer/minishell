/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:03:51 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:24:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_get_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && ft_inset(s1[start], set))
		start++;
	return (start);
}

static int	ft_get_end(char const *s1, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (end != 0 && ft_inset(s1[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimed;

	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start > end)
		len = 0;
	else
		len = end - start + 1;
	trimed = malloc(sizeof(char) * (len + 1));
	if (trimed == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimed[i] = s1[start + i];
		i++;
	}
	trimed[i] = '\0';
	return (trimed);
}
