/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:39:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/22 18:34:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_start(t_line *to_pipe)
{
	int		i;
	t_line	*tmp;
	char	*str;

	tmp = to_pipe;
	while (tmp)
	{
		if (!tmp->quote)
		{
			i = -1;
			while (tmp->line[++i])
			{
				if (tmp->line[i] = '|')
				{
					str = tmp->line;
					if (i == 0)
						tmp->quote += 1;
					else if ((unsigned long)(i + 1) == ft_strlen(tmp->line))
						tmp->quote += 2;
					else
					{
						tmp->quote += 2;
						tmp->line = ft_strndup(line, i);
						ms_line_addin(tmp, ft_strndup(&line[i], ft_strlen(tmp->line - i)));
						free(str);
						break ;
					}
				}
			}
		}
	tmp = tmp->next;
	}
	return (ms_pipe_run(t_line *to_pipe));
}
