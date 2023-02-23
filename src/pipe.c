/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:39:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 10:35:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_start(t_line *to_pipe)
{
	int		i;
	int		ret;
	t_line	*tmp;

	tmp = to_pipe;
	while (tmp)
	{
		if (tmp->quote < 9)
		{
			tmp->line = ms_utils_trim(tmp->line);
			i = -1;
			while (tmp->line[++i])
			{
				if (tmp->line[i] == '|')
				{
					if (i == 0)
						tmp->quote += 1;
					else if ((unsigned long)(i + 1) == ft_strlen(tmp->line))
						tmp->quote += 2;
					else
					{
						tmp->quote += 2;
						ret = ms_line_addin(tmp, ft_strndup(&tmp->line[i], ft_strlen(tmp->line) - (unsigned long) i));
						if (ret)
							return (ret);
						tmp->line = ft_strndup(tmp->line, i);
						if (tmp == NULL)
							return (1);
						break ;
					}
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
