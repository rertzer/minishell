/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:55:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 14:20:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_file_split(t_line **to_parse, char chevron, int i, int shift)
{
	if (i == 0)
		return (ms_file_split_beggin(to_parse, chevron, shift));
	else if ((unsigned int)(i + 1) == ft_strlen((*to_parse)->line))
		return (ms_file_split_end(to_parse, chevron, i, shift));
	else
		return (ms_file_split_middle(to_parse, chevron, i, shift));
}

int	ms_file_split_beggin(t_line **to_parse, char chevron, int shift)
{
	int		len;
	char	*str;

	str = (*to_parse)->line;
	len = ms_utils_wordlen(&str[shift]);
	if (len)
	{
		(*to_parse)->line = ft_strndup(&str[shift], len);
		if ((*to_parse)->line == NULL)
			return (ms_return_freeturn(&str, 1));
		(*to_parse)->quote = chevron;
		if ((unsigned int)(shift + len + 1) < ft_strlen(str))
		{
			if (ms_file_addin(to_parse, \
						ft_strdup(&str[shift + len + 1]), 0))
				return (ms_return_freeturn(&str, 1));
		}
		free(str);
	}
	else if (ms_file_quotenext(to_parse, chevron))
		return (1);
	return (0);
}

int	ms_file_split_end(t_line **to_parse, char chevron, int i, int shift)
{
	int		len;
	char	*str;

	str = (*to_parse)->line;
	len = ms_utils_wordlen(&str[i + shift]);
	(*to_parse)->line = ft_strndup(str, i);
	if ((*to_parse)->line == NULL)
		return (1);
	if (len)
	{
		if (ms_file_addin(to_parse, ft_strndup(&str[i + shift], len), chevron))
			return (ms_return_freeturn(&str, 1));
		(*to_parse) = (*to_parse)->next;
	}
	else if (ms_file_quotenext(to_parse, chevron))
		return (ms_return_freeturn(&str, 1));
	return (ms_return_freeturn(&str, 0));
}

int	ms_file_split_middle(t_line **to_parse, char chevron, int i, int shift)
{
	int		len;
	char	*str;

	str = (*to_parse)->line;
	len = ms_utils_wordlen(&str[i + shift]);
	(*to_parse)->line = ft_strndup(str, i);
	if ((*to_parse)->line == NULL)
		return (1);
	if (len)
	{
		if (ms_file_addin(to_parse, ft_strndup(&str[i + shift], len), chevron))
			return (ms_return_freeturn(&str, 1));
		(*to_parse) = (*to_parse)->next;
		if ((unsigned int)(i + shift + len + 1) < ft_strlen(str))
		{
			if (ms_file_addin(to_parse, \
						ft_strdup(&str[i + shift + len + 1]), 0))
				return (ms_return_freeturn(&str, 1));
		}
	}
	else if (ms_file_quotenext(to_parse, chevron))
		return (ms_return_freeturn(&str, 1));
	return (ms_return_freeturn(&str, 0));
}
