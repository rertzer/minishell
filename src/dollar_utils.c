/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:57:59 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 17:11:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ms_dollar_getnewlen(char *value);
static char	*ms_dollar_protectcopy(char *value, char *new_value);

char	*ms_dollar_protect(char *value)
{
	int		len;
	char	*new_value;

	len = ms_dollar_getnewlen(value);
	new_value = malloc(sizeof(char) * (len + 1));
	if (new_value == NULL)
		return (ms_return_null(R_MAL));
	return (ms_dollar_protectcopy(value, new_value));
}


static int		ms_dollar_getnewlen(char *value)
{
	int	i;
	int	spaces;

	spaces = 0;
	i = -1;
	while (value[++i])
	{
		if (value[i] == ' ')
			spaces++;
	}
	return (i + spaces);
}

static char	*ms_dollar_protectcopy(char *value, char *new_value)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (value[++i])
	{
		if (value[i] == ' ')
		{
			new_value[i + j] = '\\';
			j++;
		}
		new_value[i + j] = value[i];
	}
	new_value[i + j] = '\0';
	free(value);
	return (new_value);
}
