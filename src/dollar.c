/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:18:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 15:24:15 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_dollar_replace(char **line, int i, char **envp, int status);
static int	ms_dollar_copykey(char **key, char **line, int i);
static int	ms_dollar_wordlen(char *line);
static char	*ms_dollar_getvalue(char *key, int status, char **envp);

char	*ms_dollar_parse(char *line, char **envp, int status)
{
	int		i;
	int		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ms_char_prevok(line, i) \
				&& line[i + 1] && !ms_char_isin(line[i + 1], LD_CHAR))
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

static int	ms_dollar_replace(char **line, int i, char **envp, int status)
{
	int		len;
	char	*key;
	char	*value;

	key = NULL;
	len = ms_dollar_copykey(&key, line, i);
	if (len < 0)
		return (-1);
	value = ms_dollar_getvalue(key, status, envp);
	*line = ms_utils_strreplace(*line, value, i, len + 1);
	len = ft_strlen(value);
	free(key);
	free(value);
	if (*line == NULL)
		return (-1);
	return (len);
}

static int	ms_dollar_copykey(char **key, char **line, int i)
{
	int		len;

	len = 0;
	if ((*line)[i + 1])
	{
		len = ms_dollar_wordlen(&(*line)[i + 1]);
		if (len)
			*key = ft_strndup(&(*line)[i + 1], len);
		if (*key == NULL)
			return (-1);
	}
	return (len);
}

static char	*ms_dollar_getvalue(char *key, int status, char **envp)
{
	char	*value;

	value = NULL;
	if (key)
	{
		if (ft_strcmp(key, "?") == 0)
			value = ft_itoa(status);
		else
			value = ms_env_getvalue(envp, key);
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

static int	ms_dollar_wordlen(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ms_char_isin(line[len], DL_CHAR))
		len++;
	return (len);
}
