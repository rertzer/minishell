/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:47:11 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/08 17:01:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pattern_match(char *name, char *patt, int offset)
{
	int	i;
	int	j;

	i = -1 + offset;
	while (name[++i])
	{
		j = -1;
		while (patt[++j])
		{
			if (name[i + j] != patt[j])
				break ;
		}
		if (patt[j] == '\0')
			return (j);
	}
	return (-1);
}

char	*ms_pattern_anchor(char *str)
{
	int		i;
	char	edge[2];

	edge[0] = 2;
	edge[1] = '\0';
	if (str[0] != '*')
	{
		str = ms_pattern_head(edge, str);
		if (str == NULL)
				return (NULL);
	}
	i = ft_strlen(str);
	edge[0] = 3;
	if (str[i] != '*')
	{
		str = ms_pattern_tail(edge, str);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*ms_pattern_head(char *edge, char *str)
{
	char *tmp;

	tmp = ft_strjoin(edge, str);
	if (tmp == NULL)
		return (ms_return_null(R_STR));
	free(str);
	return (tmp);
}

char	*ms_pattern_tail(char *edge, char *str)
{
	char *tmp;

	tmp = ft_strjoin(str, edge);
	if (tmp == NULL)
		return (ms_return_null(R_STR));
	free(str);
	return (tmp);
}
