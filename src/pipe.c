/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:39:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 14:21:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_start(t_line *to_pipe)
{
	int		i;

	while (to_pipe)
	{
		if (to_pipe->quote == 0)
		{
			to_pipe->line = ms_utils_trim(to_pipe->line);
			i = -1;
			while (to_pipe->line[++i])
			{
				if (to_pipe->line[i] == '|')
				{
					if (ms_pipe_split(to_pipe, i))
						return (1);
					break ;
				}
			}
		}
		to_pipe = to_pipe->next;
	}
	return (0);
}

int	ms_pipe_split(t_line *to_pipe, int i)
{
	char	*str;

	str = to_pipe->line;
	to_pipe->line = ft_strndup(str, i);
	if (to_pipe == NULL)
		return (ms_return_freeturn(&str, 1));
	if (ms_utils_spaceonly(to_pipe->line))
	{
		if (ms_pipe_setpipe(to_pipe))
			return (ms_return_freeturn(&str, 1));
	}
	else
	{
		if (ms_pipe_addpipe(&to_pipe))
			return (ms_return_freeturn(&str, 1));
	}
	if (!ms_utils_spaceonly(&str[i + 1]))
	{
		if (ms_line_addin(to_pipe, ft_strndup(&str[i + 1], \
					ft_strlen(str) - (unsigned long)(i + 1))))
			return (ms_return_freeturn(&str, 1));
	}
	return (ms_return_freeturn(&str, 0));
}

int	ms_pipe_addpipe(t_line **to_pipe)
{
	if (ms_line_addin(*to_pipe, ft_strdup("|")))
		return (1);
	*to_pipe = (*to_pipe)->next;
	(*to_pipe)->quote = 'p';
	return (0);
}

int	ms_pipe_setpipe(t_line *to_pipe)
{
	free(to_pipe->line);
	to_pipe->quote = 'p';
	to_pipe->line = ft_strdup("|");
	if (to_pipe->line == NULL)
		return (1);
	return (0);
}
