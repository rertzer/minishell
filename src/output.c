/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:13:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/18 12:23:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_output_loop(t_file *file);
static int	ms_output_openfile(t_file *file);
static int	ms_output_heredoc(char *limiter);
static char	*ms_output_hereline(char *limiter, char *line, int *pipefd);

int	ms_output_openall(t_command *cmd)
{
	int	fd;

	fd = ms_output_loop(cmd->infile);
	if (fd == -1)
		return (-1);
	fd = ms_output_loop(cmd->outfile);
	return (fd);
}

static int	ms_output_loop(t_file *file)
{
	int		fd;

	fd = 1;
	while (file)
	{
		ms_msdata_close(fd);
		fd = ms_output_openfile(file);
		if (fd == -1)
			return (-1);
		file = file->next;
	}
	return (fd);
}

static int	ms_output_openfile(t_file *file)
{
	int		flags;
	int		fd;
	mode_t	mode;

	if (file->mode == '=')
		return (ms_output_heredoc(file->name));
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	flags = pp_open_flags(file->mode);
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		return (ms_return_error(-1, R_OPN));
	return (fd);
}

static int	ms_output_heredoc(char *limiter)
{
	char	*line;
	int		fd;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		return (ms_return_error(-1, "pipe"));
	fd = pipefd[0];
	line = get_next_line(0);
	while (line)
		line = ms_output_hereline(limiter, line, pipefd);
	close(pipefd[1]);
	return (fd);
}

static char	*ms_output_hereline(char *limiter, char *line, int *pipefd)
{
	int	line_size;
	int	limiter_size;

	line_size = ft_strlen(line);
	limiter_size = ft_strlen(limiter);
	if (pp_here_nolimit(line, limiter, line_size, limiter_size))
	{
		errno = 0;
		if (write(pipefd[1], line, line_size) == -1)
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
