/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 15:02:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pp_here_line(t_pipeline *ppl, char *limiter,	\
		char *line, int *pipefd);

int	pp_here_doc(t_pipeline *ppl, char *limiter)
{
	char	*line;
	int		fd;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		ms_exit_error(ppl, "pipe");
	fd = pipefd[0];
	line = get_next_line(0);
	while (line)
		line = pp_here_line(ppl, limiter, line, pipefd);
	close(pipefd[1]);
	return (fd);
}

static char	*pp_here_line(t_pipeline *ppl, char *limiter,	\
		char *line, int *pipefd)
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
			ms_exit_error(ppl, R_WRT);
		}
		free(line);
		line = get_next_line(0);
	}
	else
		pp_nullfree(&line);
	return (line);
}
