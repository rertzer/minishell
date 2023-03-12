/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:26:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 17:47:03 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_utils_spaceonly(char *str)
{
	while (*str)
	{
		if (*str != 9 && *str != 32)
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
	errno = 0;
	dest = malloc(sizeof(char) * (new_len + 1));
	if (dest == NULL)
		return (ms_return_null(R_MAL));
	i = -1;
	while (++i < offset)
		dest[i] = str[i];
	i = -1;
	while (++i < (int) ft_strlen(ins))
		dest[offset + i] = ins[i];
	i = offset - 1;
	while (++i < (int)ft_strlen(str) - len)
		dest[ft_strlen(ins) + i] = str[len + i];
	dest[ft_strlen(ins) + i] = '\0';
	free(str);
	return (dest);
}

int	ms_utils_insert(char *str, char ***table)
{
	int		i;
	int		entries;
	char	**new_tab;

	entries = 0;
	while (*table && (*table)[entries])
		entries++;
	errno = 0;
	new_tab = malloc(sizeof(char *) * (entries + 2));
	if (new_tab == NULL)
		return (ms_return_error(errno, R_MAL));
	i = -1;
	while (++i < entries)
		new_tab[i] = (*table)[i];
	new_tab[i] = str;
	new_tab[i + 1] = NULL;
	free(*table);
	*table = new_tab;
	return (0);
}
