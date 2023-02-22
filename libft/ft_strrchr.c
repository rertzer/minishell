/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:54:15 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/14 14:23:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;
	char			*found;

	if (s == NULL)
		return (NULL);
	found = NULL;
	uc = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == uc)
			found = (char *)&s[i];
		i++;
	}
	if (uc == '\0')
		found = (char *)&s[i];
	return (found);
}
