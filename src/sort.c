/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:39:41 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 14:10:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sort_sort(char **tosort)
{
	int	len;

	if (tosort == NULL)
		return ;
	len = 0;
	while (tosort[len])
		len++;
	ms_sort_loop(tosort, len);
}

void	ms_sort_loop(char **tosort, int len)
{
	int		i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = -1;
		while (++i < len - 1)
		{
			if (ft_strcmp(tosort[i], tosort[i + 1]) > 0)
				is_sorted = ms_sort_swap(tosort, i);
		}
	}
}

int	ms_sort_swap(char **tosort, int i)
{
	char	*tmp;

	tmp = tosort[i + 1];
	tosort[i + 1] = tosort[i];
	tosort[i] = tmp;
	return (0);
}
