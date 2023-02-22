/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:58:14 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/16 16:20:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	word_count(char const *s, char c);
static char	**feed_split(char **splited, char const *s, char c);
static char	**flush(char **splited);

char	**ft_split(char const *s, char c)
{
	int		word_nb;
	char	**splited;

	if (NULL == s)
		return (NULL);
	word_nb = word_count(s, c);
	splited = malloc(sizeof(char *) * (word_nb + 1));
	if (NULL == splited)
		return (NULL);
	splited[word_nb] = NULL;
	return (feed_split(splited, s, c));
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	inside;

	count = 0;
	inside = 0;
	i = -1;
	while (s[++i])
	{
		if (inside && s[i] == c)
				inside = 0;
		else if (inside == 0 && s[i] != c)
		{
			inside = 1;
			count++;
		}
	}
	return (count);
}

static char	**feed_split(char **splited, char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;

	i = 0;
	k = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c)
			i++;
		start = i;
		if (start >= ft_strlen(s))
			break ;
		while (s[i] != c && s[i])
			i++;
		splited[k] = ft_substr(s, start, i - start);
		if (NULL == splited[k])
			return (flush(splited));
		k++;
	}
	return (splited);
}

static char	**flush(char **splited)
{
	int	i;

	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
	return (NULL);
}
