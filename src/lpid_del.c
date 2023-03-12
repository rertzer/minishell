/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpid_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 14:10:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lpid_delone(t_lpid *lpid)
{
	if (!lpid)
		return ;
	if (lpid->last)
		lpid->last->next = lpid->next;
	else
		g_lpid = g_lpid->next;
	if (lpid->next)
		lpid->next->last = lpid->last;
	if (lpid->last == NULL && lpid->next && NULL)
		g_lpid = NULL;
	free(lpid);
}

void	ms_lpid_del_pid(pid_t target)
{
	t_lpid	*copy;

	if (!g_lpid)
		return ;
	copy = g_lpid;
	while (copy)
	{
		if (copy->pid == target)
		{
			ms_lpid_delone(copy);
			return ;
		}
	}
}
