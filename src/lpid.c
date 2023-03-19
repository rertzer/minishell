/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:15:25 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/19 13:13:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*ms_lpid_new(pid_t pid)
{
	t_lpid	*lpid;

	errno = 0;
	lpid = malloc(sizeof(t_lpid));
	if (!lpid)
	{
		ms_return_error(1, R_MAL);
		return (NULL);
	}
	lpid->pid = pid;
	lpid->last = NULL;
	lpid->next = NULL;
	return (lpid);
}

void	ms_lpid_add(t_lpid *new)
{
	if (!new)
		return ;
	if (g_lpid)
	{
		new->next = g_lpid;
		g_lpid->last = new;
	}
	g_lpid = new;
}

void	ms_lpid_add_back(t_lpid *new)
{
	t_lpid	*first;

	if (!new)
		return ;
	if (g_lpid)
	{
		first = g_lpid;
		while (g_lpid->next)
			g_lpid = g_lpid->next;
		g_lpid->next = new;
		new->last = g_lpid;
		g_lpid = first;
	}
	else
		g_lpid = new;
}
