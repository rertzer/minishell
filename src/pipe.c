/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:39:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 11:35:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_start(t_line *to_pipe)
{
	int		i;
	int		ret;
	char	*str;
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
					str = tmp->line;
					tmp->line = ft_strndup(tmp->line, i);
					if (tmp == NULL)
					{
						free(str);
						return (1);
					}
					if (ms_utils_spaceonly(tmp->line))
					{
						free(tmp->line);
						tmp->line = ft_strdup("|");
						tmp->quote = 'p';
					}
					else
					{
						ret = ms_line_addin(tmp, ft_strdup("|"));
						if (ret)
						{
							free(str);
							return (ret);
						}
						tmp = tmp->next;
						tmp->quote = 'p';
					}
					if (!ms_utils_spaceonly(&str[i + 1])) 
					{
						ret = ms_line_addin(tmp, ft_strndup(&str[i + 1], ft_strlen(str) - (unsigned long) (i + 1)));
						if (ret)
						{
							free(str);
							return (ret);
						}
					}
					free(str);
					break ;
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
