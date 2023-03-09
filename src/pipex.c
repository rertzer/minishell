/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:04:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 14:15:13 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipex_print(t_command *cmd_start, int cmd_nb)
{
	// remove function for submission
	printf("%d commands\n", cmd_nb);
	while (cmd_start)
	{
		printf("\ncmd %s\n", cmd_start->cmd_path);
		t_file	*file;
		file = cmd_start->infile;
		while (file)
		{
			printf("file_in: _%s_ %c\n", file->name, file->mode);
			file = file->next;
		}
		file = cmd_start->outfile;
		while (file)
		{
			printf("file_out: _%s_ %c\n", file->name, file->mode);
			file = file->next;
		}
		if (cmd_start->args)
		{
			int i = -1;
			while (cmd_start->args[++i])
				printf("arg %s\n", cmd_start->args[i]);
		}
		cmd_start = cmd_start->next;
	}
	return (0);
}
