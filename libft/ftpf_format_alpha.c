/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_format_alpha.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:27:46 by rertzer           #+#    #+#             */
/*   Updated: 2022/12/01 15:43:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_format_char(t_data *data)
{
	char	c;

	c = (char)va_arg(data->ap, int);
	write(1, &c, 1);
	return (1);
}

int	ft_format_str(t_data *data)
{
	char	*str;
	int		len;

	str = va_arg(data->ap, char *);
	if (str == NULL)
	{
		len = 6;
		write(1, "(null)", 6);
	}
	else
	{
		len = ft_strlen(str);
		write(1, str, len);
	}
	return (len);
}

int	ft_format_per(t_data *data)
{
	(void)data;
	write(1, "%", 1);
	return (1);
}

int	ft_format_wft(char c)
{
	write(1, "%", 1);
	if (c != '\0')
	{
		write(1, &c, 1);
		return (2);
	}
	return (-1);
}
