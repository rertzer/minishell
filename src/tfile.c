/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:19:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/30 14:40:13 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_tfile_insertback(t_file **start, t_file *new);

int	ms_tfile_addback(t_file **start, char *line, char mode)
{
	t_file	*new;

	errno = 0;
	new = malloc(sizeof(t_file));
	if (new == NULL)
		return (ms_return_error(1, R_MAL));
	new->name = line;
	new->mode = mode;
	new->fd = 0;
	new->next = NULL;
	ms_tfile_insertback(start, new);
	return (0);
}

static void	ms_tfile_insertback(t_file **start, t_file *new)
{
	t_file	*last;

	if (*start == NULL)
		*start = new;
	else
	{
		last = *start;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	ms_tfile_clean(t_file **start)
{
	t_file	*tmp;
	t_file	*file;

	file = *start;
	while (file)
	{
		free(file->name);
		ms_msdata_close(file->fd);
		tmp = file->next;
		free(file);
		file = tmp;
	}
	*start = NULL;
	return (0);
}
