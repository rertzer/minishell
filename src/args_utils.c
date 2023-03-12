/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:49:34 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 14:05:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_args_wildinsert(t_command *cmd, char *line, int start, int i)
{
	char	*word;
	char	**expanded;

	word = ft_strndup(&line[start], i - start);
	if (word == NULL)
		return (ms_return_msg(1, R_STR));
	expanded = ms_wildcard_start(word);
	if (expanded == NULL)
		return (ms_return_msg(1, R_STR));
	ms_sort_sort(expanded);
	if (ms_args_expinsert(cmd, expanded))
		return (1);
	free(expanded);
	return (0);
}

int	ms_args_expinsert(t_command *cmd, char **expanded)
{
	int	i;

	i = -1;
	while (expanded[++i])
	{
		if (ms_args_insert(cmd, expanded[i]))
		{
			while (expanded[++i])
				free(expanded[i]);
			free(expanded);
			return (ms_return_msg(1, R_STR));
		}
	}
	return (0);
}
