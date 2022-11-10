/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:27:23 by awooden           #+#    #+#             */
/*   Updated: 2022/10/25 21:56:52 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
//# include <readline.h>
//# include <readline/history.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# define ERROR 1
# define SUCCESS 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef	struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
} t_env_list;

typedef struct s_cmd_list
{
	char				**cmd;
	int					infd;
	int					outfd;
	struct s_cmd_list	*next;
} t_cmd_list;

typedef struct s_info
{
	t_env_list	*env_list;
	char		**env;
	char 		**heredocs;
	int			exec_status;
	int			is_exit;
} t_info; 

// Utils from Libft

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strnfind(char *str, char **str_arr, int n);
int		ft_isspace(int c);
int		ft_isnumeric(char *str);
int		ft_isdigit(int c);
unsigned long long	ft_atoull(char *str, int *minus);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
void	free_arr(char **arr);
void	pserror(char *error_text);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);

// Utils for lists

t_env_list	*env_lstnew(char *key, char *value);
t_env_list	*env_lstcopy(t_env_list *alist);
void		env_lstadd_back(t_env_list **lst, t_env_list *new);
void		env_lstremove(t_env_list **env, char *key);
t_cmd_list	*cmd_lstnew(char **value, int in, int out);
void		cmd_lstadd_back(t_cmd_list **lst, t_cmd_list *new);

// Minishell built-ins

void		ft_cd(t_info **info, char **args);
void		ft_echo(char **args, int fd);
void		ft_env(t_env_list *env_list, int fd);
void		ft_exit(t_info *info, char **args);
void		ft_export(t_info **info, char **args, int fd);
void		ft_pwd(t_info *info, int fd);
void		ft_unset(t_env_list **env_list, char **args);
int			env_add(char *key, char *val, t_env_list **env);

// Error handling

void	child_proc_err(char *err_location);
void	fork_err(t_info	**info, t_cmd_list *cmd_list, int *pids);
void	shell_err(t_info **info, t_cmd_list *cmd_list, char *err_location);
void	clear_iteration(t_info *info, t_cmd_list *cmd_list);

// Executor

int		calc_cmds(t_cmd_list *cmd_list);
char	*make_cmd(t_env_list *env, char *cmd);
t_info	*create_t_info(char	**env);
void	executor(t_info	**info, t_cmd_list *cmd_list);

#endif