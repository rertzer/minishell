/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:31:58 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 14:55:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_here_doc(char *limiter, int *fd)
{
	char	*line;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		return (1);
	*fd = pipefd[0];
	line = get_next_line(0);
	while (line)
		line = pp_here_write_line(limiter, line, pipefd);
	close(pipefd[1]);
	return (0);
}

char	*pp_here_write_line(char *limiter, char *line, int *pipefd)
{
	int	line_size;
	int	limiter_size;

	line_size = ft_strlen(line);
	limiter_size = ft_strlen(limiter);
	if (!((line_size == limiter_size + 1) && \
			(ft_strncmp(line, limiter, limiter_size) == 0)))
	{
		errno = 0;
		if (write(pipefd[1], line, line_size) == -1)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(0);
	}
	else
		pp_nullfree(&line);
	return (line);
}
