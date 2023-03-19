/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:30:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 09:20:12 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_return_freeturn(char **ptr, int ret)
{
	free(*ptr);
	ptr = NULL;
	return (ret);
}

int	ms_return_msg(int ret, char const *who, char const *what)
{
	if (NULL != who || NULL != what)
	{
		ft_putstr_fd("minishell error : ", 2);
		if (NULL != who)
			ft_putstr_fd(who, 2);
		if (NULL != who && NULL != what)
			ft_putstr_fd(" : ", 2);
		if (NULL != what)
			ft_putstr_fd(what, 2);
		ft_putstr_fd("\n", 2);
	}
	return (ret);
}

int	ms_return_error(int ret, char *msg)
{
	perror(msg);
	return (ret);
}
