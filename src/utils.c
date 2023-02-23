/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:26:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 11:14:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_utils_trim(char *str)
{
	char space[2];
	char	*dest;

	space[0] = 32;
	space[1] = 9 ;

	dest = ft_strtrim(str, space);
	free(str);
	return (dest);
}


int	ms_utils_spaceonly(char *str)
{
	while (*str)
	{
		if (*str != 9 || *str != 32)
			return (0);
		str++;
	}
	return (1);
}
