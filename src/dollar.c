/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:18:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 15:00:32 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_dollar_replace(t_msdata *msdata, char **line, int i);
static int	ms_dollar_copykey(char **key, char **line, int i);
static int	ms_dollar_wordlen(char *line);
static char	*ms_dollar_getvalue(t_msdata *msdata, char *key);

char	*ms_dollar_parse(t_msdata *msdata, char *line)
{
	int		i;
	int		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ms_char_prevok(line, i) \
				&& line[i + 1] && !ms_char_isin(line[i + 1], LD_CHAR))
		{
			len = ms_dollar_replace(msdata, &line, i);
			if (len < 0)
				return (NULL);
			i += len;
		}
		else
			i++;
	}
	return (line);
}

static int	ms_dollar_replace(t_msdata *msdata, char **line, int i)
{
	int		len;
	char	*key;
	char	*value;

	key = NULL;
	len = ms_dollar_copykey(&key, line, i);
	if (len < 0)
		return (-1);
	value = ms_dollar_getvalue(msdata, key);
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

static char	*ms_dollar_getvalue(t_msdata *msdata, char *key)
{
	char	*value;

	value = NULL;
	if (key)
	{
		if (ft_strcmp(key, "?") == 0)
			value = ft_itoa(msdata->status);
		else
			value = ms_env_getvalue(msdata->envp, key);
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
