/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 11:31:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_pipeline *ppl, char ***envp, char *msg)
{
	ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	ms_lpid_clean();
	*envp = NULL;
	if (msg)
	{
		if (msg[0] != 'Q')
			ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_exit(t_pipeline *ppl, char ***envp, char **args)
{
	int	status;

	status = 0;
	if (args)
		ms_exit_getstatus(args, &status);
	ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	ms_lpid_clean();
	*envp = NULL;
	exit(status);
}

void	ms_exit_error(t_pipeline *ppl, char *msg, char ***envp)
{
	int	error;
	error = errno;
	DP
	perror(msg);
	DP
	if (error == 13)
		error = 126;
	ms_lpid_clean();
	if (ppl)
		ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	exit(error);
}

void	ms_exit_child(char *path, char **args, char ***envp)
{
	int	error;
	
	error = errno;
	ft_putstr_fd("Minishell: ", 2);
	perror(path);
	if (error == 13)
		error = 126;
	if (error == 2)
		error = 127;
	free(path);
	ft_split_flush(args);
	ms_lpid_clean();
	ft_split_flush(*envp);
	exit(error);

}
void	ms_exit_path(t_pipeline *ppl, char *msg, char ***envp)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": command not found\n", 2);
	ms_lpid_clean();
	if (ppl)
		ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	exit(127);
}

int	ms_exit_getstatus(char **args, int *status)
{
	if (!ms_atoi(args[0], status) && args[1] != NULL)
		return (ms_return_msg(2, "exit: too many arguments"));
	return (0);
}
