/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:30:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 14:49:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_return_freeturn(char **ptr, int ret)
{
	free(*ptr);
	ptr = NULL;
	return (ret);
}

int	ms_return_msg(int ret, char *msg)
{
	if (NULL != msg)
	{
		ft_putstr_fd("minishell error : ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (ret);
}

char	*ms_return_null(char *msg)
{
	if (NULL != msg)
	{
		ft_putstr_fd("minishell error : ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (NULL);
}

int	ms_return_error(int ret, char *msg)
{
	perror(msg);
	return (ret);
}
