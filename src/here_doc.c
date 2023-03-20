/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/20 09:54:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pp_here_line(t_msdata *msdata, char *limiter, char *line,	\
		int *pipefd);

int	pp_here_doc(t_msdata *msdata, char *limiter)
{
	char	*line;
	int		fd;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		ms_exit_error(msdata, "pipe");
	fd = pipefd[0];
	line = get_next_line(0);
	while (line)
		line = pp_here_line(msdata, limiter, line, pipefd);
	close(pipefd[1]);
	return (fd);
}

static char	*pp_here_line(t_msdata *msdata, char *limiter,	\
		char *line, int *pipefd)
{
	int	line_size;
	int	limiter_size;

	line_size = ft_strlen(line);
	limiter_size = ft_strlen(limiter);
	if (pp_here_nolimit(line, limiter, line_size, limiter_size))
	{
		errno = 0;
	(void)pipefd;
		if (write(pipefd[1], line, line_size) == -1)
		{
			free(line);
			ms_exit_error(msdata, R_WRT);
		}
		free(line);
		line = get_next_line(0);
	}
	else
		pp_nullfree(&line);
	return (line);
}

int	pp_here_nolimit(char *line, char *limiter,	\
		int line_size, int limiter_size)
{
	if ((line_size == limiter_size + 1) && \
				(ft_strncmp(line, limiter, limiter_size) == 0))
		return (0);
	return (1);
}
