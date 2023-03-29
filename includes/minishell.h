/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/29 17:05:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

# include "libft.h"

# define SQ_CHAR " $*|<>\t\"'"
# define DQ_CHAR " *|<>\t"
# define QT_CHAR "'\""
# define FL_CHAR " \t<>"
# define SP_CHAR " \t"
# define DL_CHAR " \t$/"
# define LD_CHAR " \t$/\\<>'\"\001"
# define CD_CHAR " \t/"
# define HD_CHAR " \t<>|"

# define PROMPT "\001\e[1;32m\002Minishell: \001\e[0m\002"
# define HD_PATH "minishell_"
# define DP fprintf(stderr, "%s %d\n", __FILE__, __LINE__);

# define FUN_TOP 8
# define NOT_FOUND 127
# define NOT_EXEC 126

# define R_NVI "not a valid identifier"
# define R_AMB "ambigous redirect"
# define R_STR "string error"
# define R_SPL "split error"
# define R_MAL "malloc error"
# define R_PAT "path not found"
# define R_WRT "write error"
# define R_CMD "command not found"
# define R_FRK "fork error"
# define R_PIP "pipe error"
# define R_SYN "syntax error"
# define R_OPN "open error"
# define R_NUM "numeric argument required"
# define R_SNP "string not in pwd"
# define R_TMA "too many arguments"
# define R_TTY "ttyslot error"
# define R_TCG "tcgetattr error"

typedef struct s_file
{
	char			*name;
	char			mode;
	struct s_file	*next;
}				t_file;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	struct s_file		*filelst;
	char				*cmd_path;
	char				**args;
	int					cmd_nb;
	struct s_command	*next;
}				t_command;

typedef struct s_msdata
{
	int			status;
	int			cmd_nb;
	t_command	*cmds;
	int			(*pipefd)[2];
	char		**envp;
}				t_msdata;

typedef struct s_lpid
{
	pid_t				pid;
	struct s_lpid		*next;
	struct s_lpid		*last;
}				t_lpid;

typedef struct s_term
{
	struct termios		interact_tio;
	struct termios		process_tio;
	int					tty_device;
}				t_term;

typedef int		(*t_builtin_fun)(t_msdata *msdata, t_command *cmd, int fd_out);

extern t_lpid	*g_lpid;

/* ===================================================================== */
/*                            main and signals                           */
/* ===================================================================== */
/* lpid */
t_lpid	*ms_lpid_new(pid_t pid);
void	ms_lpid_add(t_lpid *new);
void	ms_lpid_add_back(t_lpid *new);
/* lpid del */
void	ms_lpid_clean(void);
void	ms_lpid_delone(t_lpid *lpid);
void	ms_lpid_del_pid(pid_t target);
/* signal */
void	ms_signal_kill_child(int signum);
void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context);

/* ================================================================= */
/*                           Builtins                                */
/* ================================================================= */
/* builtin */
int		ms_builtin_itis(char *name);
int		ms_builtin_run(t_msdata *msdata, t_command *cmd, int fd_out);
/* cd */
int		ms_cd_run(t_msdata *msdata, t_command *cmd, int fd_out);
/* cd_utils */
char	*ms_cd_simplify(char **dirlst);
int		ms_cd_return(int ret, char *path, char *new_path);
/* echo */
int		ms_echo_run(t_msdata *msdata, t_command *cmd, int fd_out);
/* env */
char	*ms_env_getvalue(char **envp, char *key);
int		ms_env_getindex(char **envp, char *key);
int		ms_env_run(t_msdata *msdata, t_command *cmd, int fd_out);
/* export */
int		ms_export_run(t_msdata *msdata, t_command *cmd, int fd_out);
int		ms_export_arg(t_msdata *msdata, char *arg);
/* pwd */
int		ms_pwd_run(t_msdata *msdata, t_command *cmd, int fd_out);
/* unset */
int		ms_unset_run(t_msdata *msdata, t_command *cmd, int fd_out);

/* ================================================================= */
/*                        parse and run                              */
/* ================================================================= */
/* args */
int		ms_args_start(t_msdata *msdata);
int		ms_args_add(t_command *cmd, char *line);
int		ms_args_getnb(t_command *cmd);
int		ms_args_insert(t_command *cmd, char *line);
/* args parse */
int		ms_args_argsparse(t_command *cmd);
/* atoi */
int		ms_atoi(t_msdata *msdata, const char *nptr);
/* backtrack */
int		ms_backtrack_backtrack(char prev, char *pattern, char *name);
/* char */
int		ms_char_isin(char c, char *special);
int		ms_char_nextexist(char *line);
int		ms_char_prevok(char *line, int i);
char	*ms_char_unprotect(char *line);
/* command */
int		ms_command_addback(t_command **cmd_start);
int		ms_command_clean(t_msdata *msdata);
/* msdata */
void	ms_msdata_init(t_msdata *msdata);
void	ms_msdata_clean(t_msdata *msdata);
void	ms_msdata_close(int fd);
/* dollar */
char	*ms_dollar_parse(t_msdata *msdata, char *line);
/* exit */
void	ms_exit_msg(t_msdata *msdata, char *msg);
void	ms_exit_error(t_msdata *msdata, char *msg);
void	ms_exit_child(t_msdata *msdata, char *path, char **args);
void	ms_exit_path(t_msdata *msdata, char *msg);
void	ms_exit_exit(t_msdata *msdata, char **args);
/* exit run */
int		ms_exit_run(t_msdata *msdata, t_command *cmd, int fd_out);
int		ms_exit_seterror(int error);
int		ms_exit_resetstatus(t_msdata *msdata, char **args);
/* file chevron */
int		ms_file_chevron(t_command *cmd, int mode);
/* file wildcard */
char	*ms_file_wildcard(char *word);
/* output */
int		ms_output_openall(t_command *cmd);
/* parsing */
int		ms_parsing_start(t_msdata *msdata, char *line);
/* pipe */
int		ms_pipe_start(t_msdata *msdata, char *line);
/* pipeline */
int		ms_pipeline_start(t_msdata *msdata);
void	ms_pipeline_clean(t_msdata *msdata);
/* return */
int		ms_return_freeturn(char **ptr, int ret);
int		ms_return_msg(int ret, char const *who, char const *what);
int		ms_return_error(int ret, char *msg);
/* return null */
char	*ms_return_null(char *msg);
char	*ms_return_nullerror(char *msg);
char	**ms_return_null2error(char *msg);
/* sort */
void	ms_sort_sort(char **tosort);
/* tfile */
int		ms_tfile_addback(t_file **start, char *parsed, char mode);
int		ms_tfile_clean(t_file **file);
/* trim */
char	*ms_trim_trim(char *line);
/* utils */
int		ms_utils_spaceonly(char *str);
int		ms_utils_isonly(char *str, char c);
int		ms_utils_wordlen(char *str);
char	*ms_utils_strreplace(char *str, char *ins, int offset, int len);
int		ms_utils_insert(char *str, char ***table);
/* wildcard */
char	**ms_wildcard_start(char *line);
/* *********************************************************************/
/*                            here doc                                 */
/* *********************************************************************/
/* hd loop */
int		ms_hdloop_start(t_msdata *msdata);
/* here doc */
int		pp_here_doc(char *limiter, char *filename);
int		pp_here_nolimit(char *line, char *limiter,	\
		int line_size, int limiter_size);
/* **********************************************************************/
/*                               pipex                                  */
/* **********************************************************************/
/* check_cmd */
void	pp_check_cmd_path(t_msdata *msdata, t_command *cmd);
/* Run */
int		pp_run_pipe(t_msdata *msdata);
void	pp_run_close_pipes(t_msdata *msdata);
int		pp_run_wait(void);
/* Open */
void	pp_open_filelst(t_msdata *msdata, t_command *cmd, int i);
int		pp_open_flags(char mode);
/* Child */
void	pp_child_run(t_msdata *msdata, t_command *cmd, int i);
/* Utils */
void	pp_nullfree(char **ptr);
int		pp_path_size(char const *s1, char const *s2);
char	*pp_pathjoin(char const *s1, char const *s2);
int		pp_duplicate(char const *src, char *dest, int shift);
#endif
