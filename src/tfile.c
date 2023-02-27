/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:19:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/26 15:33:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_tfile_addback(t_file **start, t_line *parsed)
{
	t_file	*new;
	t_file	*last;

	new = malloc(sizeof(t_file));
	if (new == NULL)
		return (1);
	new->name = parsed->line;
	new->mode = parsed->quote;
	new->next = NULL;
	if (*start == NULL)
		*start = new;
	else
	{
		last = *start;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (0);
}

int	ms_tfile_clean(t_file **start)
{
	t_file	*tmp;
	t_file	*file;

	tmp = *start;
	while (file)
	{
		free(file->name);
		tmp = file->next;
		free(file);
		file = tmp;
	}
	*start = NULL;
	return (0);
}
