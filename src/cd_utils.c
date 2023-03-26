/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:38:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/26 16:14:23 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cd_isdoubledot(char *dir);
static int	ms_cd_removeprevious(char **dirlst, int current);
static char	*ms_cd_recompose(char **dirlst);

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
		else if (ms_cd_isdoubledot(dirlst[i]))
			ms_cd_removeprevious(dirlst, i);
	}
	return (ms_cd_recompose(dirlst));
}

static int	ms_cd_isdoubledot(char *dir)
{
	if (dir[0] == '.' && dir[1] == '.' && dir[2] == '\0')
		return (1);
	return (0);
}

static int	ms_cd_removeprevious(char **dirlst, int current)
{
	int	i;

	i = current;
	while (--i >= 0)
	{
		if (dirlst[i][0] == '\0')
			continue ;
		dirlst[i][0] = '\0';
		break ;
	}
	dirlst[current][0] = '\0';
	return (0);
}

static char	*ms_cd_recompose(char **dirlst)
{
	int		i;
	char	*tmp;
	char	*new_path;

	new_path = NULL;
	if (dirlst[0][0] == '\0')
		new_path = ft_strdup("/");
	i = -1;
	while (dirlst[++i])
	{
		if (dirlst[i][0] == '\0')
			continue ;
		tmp = new_path;
		if (tmp == NULL && new_path != NULL)
			return (ms_return_null(R_STR));
		new_path = pp_pathjoin(tmp, dirlst[i]);
		free(tmp);
		if (new_path == NULL)
			return (NULL);
	}
	dirlst = ft_split_flush(dirlst);
	return (new_path);
}

int	ms_cd_return(int ret, char *path, char *new_path)
{
	free(path);
	free(new_path);
	return (ret);
}
