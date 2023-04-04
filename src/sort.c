/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:39:41 by rertzer           #+#    #+#             */
/*   Updated: 2023/04/04 11:42:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_sort_loop(char **tosort, int len);
static int	ms_sort_cmp(const char *s1, const char *s2);
static int	ms_sort_swap(char **tosort, int i);
static void	ms_sort_tolow(char *str);

void	ms_sort_sort(char **tosort)
{
	int	len;

	if (tosort == NULL)
		return ;
	len = 0;
	while (tosort[len])
		len++;
	ms_sort_loop(tosort, len);
}

static void	ms_sort_loop(char **tosort, int len)
{
	int		i;
	int		is_sorted;
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = -1;
		while (++i < len - 1)
		{
			if (ms_sort_cmp(tosort[i], tosort[i + 1]) > 0)
				is_sorted = ms_sort_swap(tosort, i);
		}
	}
}

static int	ms_sort_cmp(const char *s1, const char *s2)
{
	size_t	i;
	char	*s1low;
	char	*s2low;
	int		ret;
	
	s1low = ft_strdup(s1);
	s2low = ft_strdup(s2);
	ms_sort_tolow(s1low);
	ms_sort_tolow(s2low);
	i = 0;
	while (s1low[i] && s1low[i] == s2low[i])
		i++;
	ret = (unsigned char)s1low[i] - (unsigned char)s2low[i];
	free(s1low);
	free(s2low);
	return (ret);
}

static int	ms_sort_swap(char **tosort, int i)
{
	char	*tmp;

	tmp = tosort[i + 1];
	tosort[i + 1] = tosort[i];
	tosort[i] = tmp;
	return (0);
}


static void	ms_sort_tolow(char *str)
{
	int	i = -1;

	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
}
