/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:26:02 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/23 17:26:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	buff;
	char			*str;
	t_list			*line;

	line = malloc(sizeof(t_list));
	if (NULL == line)
		return (NULL);
	line->string = malloc(sizeof(char));
	if (NULL == line->string)
	{
		free(line);
		return (NULL);
	}
	line->string[0] = '\0';
	line->len = 0;
	line->next = NULL;
	line->prev = NULL;
	str = get_line(fd, line, &buff);
	clean_list(line);
	return (str);
}

void	clean_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
	}
}

char	*get_line(int fd, t_list *line, t_buffer *buff)
{
	ssize_t	toappend_len;
	t_list	*last;

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

char	*list_join(t_list *line)
{
	ssize_t		len;
	t_list		*lst;
	char		*str;

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
