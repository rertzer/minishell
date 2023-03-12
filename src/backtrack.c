/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:27:22 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 11:30:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_backtrack_backtrack(char prev, char *pattern, char *name)
{
	int	ret;

	ret = 0;
	if (name[0] == '\0' && pattern[0] == '\0')
		ret = 1;
	else if (name[0] == '\\')
		ret = ms_backtrack_backtrack(pattern[0], &pattern[1], name);
	else
	{
		if (name[0] != '\0' && ms_backtrack_match(prev, *pattern, *name))
			ret = ms_backtrack_backtrack(pattern[0], &pattern[1], &name[1]);
		else if (ret != 1 && ms_backtrack_iswildcard(prev, *pattern))
		{
			if (name[0] != '\0')
				ret = ms_backtrack_backtrack(prev, pattern, &name[1]);
			if (ret != 1)
				ret = ms_backtrack_backtrack(pattern[0], &pattern[1], &name[0]);
		}
	}
	return (ret);
}

int	ms_backtrack_match(char prev, char pattern, char name)
{
	(void)prev;
	if (pattern == name)
		return (1);
	return (0);
}

int	ms_backtrack_iswildcard(char prev, char pattern)
{
	if (prev != '\\' && pattern == '*')
		return (1);
	return (0);
}
