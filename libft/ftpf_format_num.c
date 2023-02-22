/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_format_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:30:06 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:44:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_int(t_data *data)
{
	return (str_print(ft_itoa(va_arg(data->ap, int))));
}

int	ft_format_uns(t_data *data)
{
	return (str_print(ft_uxitoa(va_arg(data->ap, unsigned int), BASETEN)));
}

int	ft_format_lhx(t_data *data)
{
	return (str_print(ft_uxitoa(va_arg(data->ap, unsigned int), BASELHEX)));
}

int	ft_format_uhx(t_data *data)
{
	return (str_print(ft_uxitoa(va_arg(data->ap, unsigned int), BASEUHEX)));
}

int	ft_format_point(t_data *data)
{
	t_ull	p;

	p = va_arg(data->ap, t_ull);
	if (p)
		return (str_print(ft_pointoa(p)));
	write(1, "(nil)", 5);
	return (5);
}
