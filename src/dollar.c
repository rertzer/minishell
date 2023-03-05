/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:18:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 09:11:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_dollar_parse(char *line, char **envp)
{
	int		i;
	int		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ms_char_prevok(line, i))
		{
			len = ms_dollar_replace(&line, i, envp);
			if (len < 0)
				return (NULL);
			i += len;
		}
		else
			i++;
	}
	return (line);
}

int	ms_dollar_replace(char **line, int i, char **envp)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	key = NULL;
	value = NULL;
	if ((*line)[i + 1])
	{
		len = ms_utils_wordlen(&(*line)[i + 1]);
		if (len)
			key = ft_strndup(&(*line)[i + 1], len);
	}
	if (key)
		value = ms_env_getvalue(envp, key);
	*line = ms_utils_strreplace(*line, value, i, len + 1);
	len = ft_strlen(value);
	free(key);
	free(value);
	if (*line == NULL)
		return (-1);
	return (len);
}
