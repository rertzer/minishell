/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:47:00 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/22 16:37:06 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	const char	prompt[] = "minishell: ";
	char		*line = NULL;

	printf("start\n");
	while (1)
	{
		line = readline(prompt);
		if (!line)
			break;
		add_history(line);
		ms_parsing_start(line);
		//free(line);
	}
	return (0);
}
