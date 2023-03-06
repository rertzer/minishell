/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:15:25 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/06 11:08:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*ms_lpid_new(pid_t pid)
{
	t_lpid	*lpid;

	lpid = malloc(sizeof(t_lpid));
	if (!lpid)
		return (NULL); // malloc error
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

void	ms_lpid_print(void) //temporaire
{
	t_lpid	*copy;
	int		i;

	copy = g_lpid;
	i = 1;
	if (!g_lpid)
	{
		printf("\e[1;31mEmpty gl_pid\n\e[0m");
		return ;
	}
	printf("\e[1;33m[%d] got : \e[0m", getpid());
	while (copy->last)
	{
		copy = copy->last;
	}
	while (copy)
	{
		printf("\e[1;34mpid[%d]-N%d \e[0m", copy->pid, i++);
		if (copy->next)
			printf("----> ");
		copy = copy->next;
	}
	printf("\n");
}
