/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:36:06 by rertzer           #+#    #+#             */
/*   Updated: 2023/01/07 10:30:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_buffer	*buff[FD_MAX];
	char			*str;
	t_gnllist		*line;

	if (fd >= FD_MAX)
		return (NULL);
	if (fd < 0)
		return (gnl_clean_one(buff, fd));
	buff[fd] = init_buffer(buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	line = malloc(sizeof(t_gnllist));
	if (NULL == line)
		return (NULL);
	line->string = malloc(sizeof(char));
	if (NULL == line->string)
		return (NULL);
	line->string[0] = '\0';
	line->len = 0;
	line->next = NULL;
	line->prev = NULL;
	str = get_line(fd, line, buff[fd]);
	clean_all(line, buff, fd);
	return (str);
}

char	*gnl_clean_one(t_buffer **buff, int fd)
{
	if (fd < -2)
	{
		fd = -1 * fd;
		if (buff[fd])
		{
			free(buff[fd]);
			buff[fd] = NULL;
		}
	}
	return (NULL);
}

void	clean_all(t_gnllist *list, t_buffer **buff, int fd)
{
	t_gnllist	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
	}
	if (buff[fd]->buffer[buff[fd]->start] == '\0')
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
}

char	*get_line(int fd, t_gnllist *line, t_buffer *buff)
{
	ssize_t		toappend_len;
	t_gnllist	*last;

	last = line;
	while (! last->len || last->string[last->len - 1] != '\n')
	{
		if (buffer_update(fd, buff) <= 0)
			return (list_join(line));
		toappend_len = get_toappend_len(&buff->buffer[buff->start]);
		last = ft_strappend(last, &buff->buffer[buff->start], toappend_len);
		buff->start += toappend_len;
	}
	return (list_join(line));
}

char	*list_join(t_gnllist *line)
{
	ssize_t			len;
	t_gnllist		*lst;
	char			*str;

	lst = line;
	len = 0;
	while (lst)
	{
		len += lst->len;
		lst = lst->next;
	}
	if (len == 0)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	list_join_util(line, str);
	return (str);
}
