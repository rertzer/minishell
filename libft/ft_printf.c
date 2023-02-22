/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:07:58 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:47:03 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fs, ...)
{
	t_data	data;

	data.fs = fs;
	data.len = 0;
	va_start(data.ap, fs);
	data.len = parse_fs(&data);
	va_end(data.ap);
	return (data.len);
}

int	parse_fs(t_data *data)
{
	int		i;
	int		start;
	int		len;

	start = 0;
	i = -1;
	while (data->fs[++i])
	{
		if (data->fs[i] == '%')
		{
			len = parse_format(data, start, i);
			if (len < 0)
				return (len);
			data->len += len;
			i++;
			start = i + 1;
		}	
	}
	len = get_string(data->fs, start, i - 1);
	if (len < 0)
		data->len = len;
	else
		data->len += len;
	return (data->len);
}

int	parse_format(t_data *data, int start, int i)
{
	int	lens;
	int	lenv;

	lens = get_string(data->fs, start, i - 1);
	lenv = get_va(data->fs[++i], data);
	if (lenv >= 0)
		lenv += lens;
	return (lenv);
}

int	get_va(char c, t_data *data)
{
	int		i;
	t_vafun	fun;

	i = ft_instr(FORMAT_STR, c);
	fun = get_fun(i);
	if (fun != NULL)
		i = fun(data);
	else
		i = ft_format_wft(c);
	return (i);
}

t_vafun	get_fun(int i)
{
	t_vafun	funtab[FORMAT_NBR];

	funtab[0] = &ft_format_char;
	funtab[1] = &ft_format_str;
	funtab[2] = &ft_format_point;
	funtab[3] = &ft_format_int;
	funtab[4] = &ft_format_int;
	funtab[5] = &ft_format_uns;
	funtab[6] = &ft_format_lhx;
	funtab[7] = &ft_format_uhx;
	funtab[8] = &ft_format_per;
	if (i < 0 || i > FORMAT_NBR)
		return (NULL);
	return (funtab[i]);
}
