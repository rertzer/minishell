/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:01:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 15:47:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_redirect_ambigous(char **expanded);

char	*ms_redirect_start(char *word)
{
	char	*redirected;
	char	**expanded;

	if (word == NULL)
		return (NULL);
	expanded = ms_wildcard_start(word);
	if (expanded == NULL)
		return (NULL);
	if (expanded[1] != NULL)
		return (ms_redirect_ambigous(expanded));
	redirected = expanded[0];
	free(expanded);
	return (redirected);
}

static char	*ms_redirect_ambigous(char **expanded)
{
	ft_split_flush(expanded);
	return (ms_return_null(R_AMB));
}
