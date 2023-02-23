/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:47:00 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 10:47:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	const char	prompt[] = "minishell: ";
	char		*line = NULL;

	(void)argc;
	(void)argv;
	printf("start\n");
	while (1)
	{
		line = readline(prompt);
		if (!line)
			break;
		add_history(line);
		ms_parsing_start(line, envp);
		//free(line);
	}
	return (0);
}