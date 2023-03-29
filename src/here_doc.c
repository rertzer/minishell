/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/29 16:24:15 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pp_here_open(char *filename);
static char	*pp_here_line(char *limiter, char *line, int fd);

int	pp_here_doc(char *limiter, char *filename)
{
	char	*line;
	int		fd;

	fd = pp_here_open(filename);
	if (fd == -1)
		return (1);
	line = get_next_line(0);
	while (line)
		line = pp_here_line(limiter, line, fd);
	close(fd);
	return (0);
}

static int	pp_here_open(char *filename)
{
	int	fd;

	errno = 0;
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (ms_return_error(1, filename));
	return (fd);
}

static char	*pp_here_line(char *limiter, char *line, int fd)
{
	int	line_size;
	int	limiter_size;

	line_size = ft_strlen(line);
	limiter_size = ft_strlen(limiter);
	if (pp_here_nolimit(line, limiter, line_size, limiter_size))
	{
		errno = 0;
		if (write(fd, line, line_size) == -1)
		{
			free(line);
			return (ms_return_nullerror(R_WRT));
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
