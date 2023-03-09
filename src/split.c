/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:59:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 13:09:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_count(char const *s, char c);
static char	**feed_split(char **splited, char const *s, char c);

char	**ms_split_protected(char const *s, char c)
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
	int		i;
	int		count;
	int		inside;
	char	prev;

	count = 0;
	inside = 0;
	prev = '\0';
	i = -1;
	while (s[++i])
	{
		if (inside && s[i] == c && prev != '\\')
				inside = 0;
		else if (inside == 0 && (s[i] != c || prev == '\\'))
		{
			inside = 1;
			count++;
		}
		prev = s[i];
	}
	return (count);
}

static char	**feed_split(char **splited, char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;
	char	prev;

	i = 0;
	k = 0;
	prev = '\0';
	while (i < ft_strlen(s))
	{
		while (s[i] == c && prev != '\\')
			i++;
		start = i;
		if (start >= ft_strlen(s))
			break ;
		while ((s[i] != c || prev == '\\') && s[i])
			i++;
		splited[k] = ft_substr(s, start, i - start);
		if (NULL == splited[k])
			return (ft_split_flush(splited));
		k++;
	}
	return (splited);
}
