/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_printf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:31:29 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:45:05 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_instr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	get_string(const char *fd, int start, int end)
{
	int	len;

	len = end - start + 1;
	write(1, &fd[start], len);
	return (len);
}

int	str_print(char *str)
{
	int		len;

	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	write (1, str, len);
	free(str);
	return (len);
}
