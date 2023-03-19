/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:26:34 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 09:20:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_atoi_setparams(const char *nptr, int *i, int *sign);
static int	ms_atoi_error(t_msdata *msdata, char const *nptr);

int	ms_atoi(t_msdata *msdata, const char *nptr)
{
	int	i;
	int	sign;
	int	total;

	ms_atoi_setparams(nptr, &i, &sign);
	total = 0;
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			total = total * 10 + nptr[i] - 48;
		else
			return (ms_atoi_error(msdata, nptr));
		i++;
	}
	msdata->status = sign * total;
	return (0);
}

static void	ms_atoi_setparams(const char *nptr, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (nptr[*i] \
			&& ((nptr[*i] >= '\t' && nptr[*i] <= '\r') \
			|| nptr[*i] == ' '))
		(*i)++;
	if (nptr[*i] == '-')
		*sign = -1;
	if (nptr[*i] == '+' || nptr[*i] == '-')
		(*i)++;
}

static int	ms_atoi_error(t_msdata *msdata, char const *nptr)
{
	msdata->status = 1;
	return (ms_return_msg(2, nptr, R_NUM));
}
