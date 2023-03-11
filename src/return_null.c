/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:24:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/11 12:25:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_return_null(char *msg)
{
	if (NULL != msg)
	{
		ft_putstr_fd("minishell error : ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (NULL);
}

char	*ms_return_nullerror(char *msg)
{
	perror(msg);
	return (NULL);
}

char	**ms_return_null2error(char *msg)
{
	perror(msg);
	return (NULL);
}
