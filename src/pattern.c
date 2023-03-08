/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:47:11 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/08 13:32:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pattern_match(char *name, char *patt, int offset)
{
	int	i;
	int	j;

	i = -1 + offset;
	while (name[++i])
	{
		j = -1;
		while (patt[++j])
		{
			if (name[i + j] != patt[j])
				break ;
		}
		if (patt[j] == '\0')
			return (1);
	}
	return (0);
}
