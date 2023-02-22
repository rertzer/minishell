/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:45 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/15 09:10:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*dest;

	slen = ft_strlen(s);
	if (start + len > slen)
		len = slen - start;
	if (!(start < slen))
	{
		len = 0;
		start = 0;
	}
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		dest[i] = s[start + i];
			i++;
	}
	dest[i] = '\0';
	return (dest);
}
