/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:57:18 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/23 11:57:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	buffer_update(int fd, t_buffer *buff)
{
	ssize_t	len;

	if (buff->buffer[buff->start])
		len = 1;
	else
		len = 0;
	if (0 == len)
	{
		buff->start = 0;
		len = read(fd, buff->buffer, BUFFER_SIZE);
		if (len >= 0)
			buff->buffer[len] = '\0';
		else
			buff->buffer[0] = '\0';
	}
	return (len);
}

t_list	*ft_strappend(t_list *last, char *src, ssize_t len)
{
	ssize_t	i;
	t_list	*dest;

	dest = malloc(sizeof(t_list));
	if (NULL == dest)
		return (NULL);
	dest->next = NULL;
	dest->prev = last;
	last->next = dest;
	dest->string = malloc(sizeof(char) * (len + 1));
	if (NULL == dest)
		return (NULL);
	dest->len = len;
	i = -1;
	while (++i < len)
		dest->string[i] = src[i];
	dest->string[i] = '\0';
	return (dest);
}

void	list_join_util(t_list *line, char *str)
{
	ssize_t		len;
	int			i;

	len = 0;
	while (line)
	{
		i = -1;
		while (line->string[++i])
			str[len + i] = line->string[i];
		str[len + i] = '\0';
		len += i;
		line = line->next;
	}
}
