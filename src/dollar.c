/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:18:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 15:24:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_dollar_parse(char *line, char **envp, int status)
{
	int		i;
	int		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ms_char_prevok(line, i))
		{
			len = ms_dollar_replace(&line, i, envp, status);
			if (len < 0)
				return (NULL);
			i += len;
		}
		else
			i++;
	}
	return (line);
}

int	ms_dollar_replace(char **line, int i, char **envp, int status)
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
		if (key == NULL)
			return (-1);
	}
	if (key)
	{
		if (ft_strcmp(key, "?") == 0)
			value = ft_itoa(status);
		else
			value = ms_env_getvalue(envp, key);
	}
	if (value == NULL)
		value = ft_strdup("");
	*line = ms_utils_strreplace(*line, value, i, len + 1);
	len = ft_strlen(value);
	free(key);
	free(value);
	if (*line == NULL)
		return (-1);
	return (len);
}
