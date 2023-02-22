/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:40:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/01/07 10:30:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

t_gnllist	*ft_strappend(t_gnllist *last, char *src, ssize_t len)
{
	ssize_t		i;
	t_gnllist	*dest;

	dest = malloc(sizeof(t_gnllist));
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

void	list_join_util(t_gnllist *line, char *str)
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

t_buffer	*init_buffer(t_buffer *buff)
{
	if (buff)
		return (buff);
	buff = malloc(sizeof(t_buffer));
	if (NULL == buff)
		return (NULL);
	buff->start = 0;
	buff->buffer[0] = '\0';
	return (buff);
}

ssize_t	get_toappend_len(char *buffer)
{
	ssize_t	len;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}
