/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:47:00 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:20:26 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **old_envp)
{
	const char	prompt[] = "minishell: ";
	char		*line = NULL;
	char		**envp;

	(void)argc;
	(void)argv;
	envp = ft_2Dstrdup(old_envp);
	while (1)
	{
		line = readline(prompt);
		if (!line)
			break;
		add_history(line);
		ms_parsing_start(line, &envp);
		//free(line);
	}
	return (0);
}
