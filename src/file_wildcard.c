/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:22:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/18 11:22:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_file_ambigous(char **expanded);

char	*ms_file_wildcard(char *word)
{
	char	*redirected;
	char	**expanded;

	if (word == NULL)
		return (NULL);
	expanded = ms_wildcard_start(word);
	if (expanded == NULL)
		return (NULL);
	if (expanded[1] != NULL)
		return (ms_file_ambigous(expanded));
	redirected = expanded[0];
	free(expanded);
	return (redirected);
}

static char	*ms_file_ambigous(char **expanded)
{
	ft_split_flush(expanded);
	return (ms_return_null(R_AMB));
}
