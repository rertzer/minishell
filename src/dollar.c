/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:57:05 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 17:06:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_dollar_parse(t_line *to_parse, char **envp)
{
	int		ret;

	ret = 0;
	while (to_parse)
	{
		if (to_parse->quote != '\'')
			ret = ms_dollar_parseline(to_parse, envp);
		if (ret)
			break ;
		to_parse = to_parse->next;
	}
	return (ret);
}

int	ms_dollar_parseline(t_line *to_parse, char **envp)
{
	int		i;
	int		len;

	i = 0;
	while (to_parse->line[i])
	{
		if (to_parse->line[i] == '$')
		{
			len = ms_dollar_replace(to_parse, i, envp);
			if (len < 0)
				return (1);
			i += len;
		}
		else
			i++;
	}
	return (0);
}

int	ms_dollar_replace(t_line *to_parse, int i, char **envp)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	key = NULL;
	value = NULL;
	if (to_parse->line[i + 1])
	{
		len = ms_utils_wordlen(&to_parse->line[i + 1]);
		if (len)
			key = ft_strndup(&to_parse->line[i + 1], len);
	}
	if (key)
		value = ms_env_getvalue(envp, key);
	to_parse->line = ms_utils_strreplace(to_parse->line, value, i, len + 1);
	len = ft_strlen(value);
	free(key);
	free(value);
	if (to_parse->line == NULL)
		return (-1);
	return (len);
}
