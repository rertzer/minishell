/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:26:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 16:22:24 by rertzer          ###   ########.fr       */
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

int	ms_utils_wordlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != 32 && str[len] != 9 && str[len] != '$')
		len++;
	return (len);
}

char	*ms_utils_strreplace(char *str, char *ins, int offset, int len)
{
	int		i;
	int		new_len;
	char	*dest;

	new_len = ft_strlen(str) + ft_strlen(ins) - len;
	dest = malloc(sizeof(char) * (new_len + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < offset)
		dest[i] = str[i];
	i = -1;
	while (++i < (int) ft_strlen(ins))
		dest[offset + i] = ins[i];
	i =  offset - 1;
	while (++i < (int)ft_strlen(str) - len)
		dest[ft_strlen(ins) + i] = str[len + i];
	dest[ft_strlen(ins) + i] = '\0';
	free(str);
	return (dest);
}
