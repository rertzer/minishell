/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:38:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:39:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd_isdbldot(char *dir)
{
	if (dir[0] == '.' && dir[1] == '.' && dir[2] == '\0')
		return (1);
	return (0);
}

int	ms_cd_rmprev(char **dirlst, int current)
{
	int	i;

	i = current;
	while (--i >= 0)
	{
		if (ms_cd_isdbldot(dirlst[i]) || dirlst[i][0] == '\0')
			continue ;
		dirlst[i][0] = '\0';
		dirlst[current][0] = '\0';
		return (1);
	}
	return (0);
}

char	*ms_cd_recompose(char **dirlst)
{
	int		i;
	char	*tmp;
	char	*new_path;

	new_path = NULL;
	i = -1;
	while (dirlst[++i])
	{
		if (dirlst[i][0] == '\0')
			continue ;
		tmp = ft_strdup(new_path);
		if (tmp == NULL && new_path != NULL)
			return (ms_return_null(R_STR));
		new_path = pp_pathjoin(tmp, dirlst[i]);
		free(tmp);
		if (new_path == NULL)
			return (NULL);
	}
	return (new_path);
}

char	*ms_cd_simplify(char **dirlst)
{
	int		i;

	i = -1;
	while (dirlst[++i])
	{
		if (dirlst[i][0] == '\0')
			continue ;
		else if (dirlst[i][0] == '.' && dirlst[i][1] == '\0')
			dirlst[i][0] = '\0';
		else if (ms_cd_isdbldot(dirlst[i]))
			ms_cd_rmprev(dirlst, i);
	}
	return (ms_cd_recompose(dirlst));
}
