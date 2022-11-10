/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:37:48 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 22:04:51 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_cmds(t_cmd_list *cmd_list)
{
	int	res;

	res = 0;
	while (cmd_list)
	{
		res++;
		cmd_list = cmd_list->next;
	}
	return (res);
}

static void	end_exec(t_info	**info, t_cmd_list *cmd_list, int *pids, int cmdc)
{
	int	status;
	int	i;

	clear_iteration(*info, cmd_list);
	i = -1;
	while (cmdc-- > 0)
	{
		if (pids[++i] != -1)
			waitpid(pids[i], &status, 0);
	}
	if (pids[i] != -1)
		(*info)->exec_status = status / 256;//dunno abt status
	free(pids);
}

static void	exec_nonbuiltin(t_info *info, t_cmd_list *cmd_list)
{
	char	**cmd_flags;
	char	*cmd_no_flags;

	// 	printf("%s", cmd_list->cmd[0]);
	// 	printf("%d", cmd_list->infd);
	// 	printf("%d\n", cmd_list->outfd);
	// exit(0);
	cmd_flags = cmd_list->cmd;
	cmd_no_flags = make_cmd(info->env_list, cmd_flags[0]);
	dup2(cmd_list->infd, STDIN);
	dup2(cmd_list->outfd, STDOUT);
	while (cmd_list)
	{
		if (close(cmd_list->infd) || close(cmd_list->outfd))
			ft_putendl_fd("Warning: failed to close fd", STDERR);
		cmd_list = cmd_list->next;
	}
	execve(cmd_no_flags, cmd_flags, NULL);
	child_proc_err("execve failed");
	exit(errno);
}

static void	exec_cmd(t_info	**info, t_cmd_list *cmd_list, int **pids, \
					int cmd_num)
{
	char	*cmd;

	cmd = cmd_list->cmd[0];
	if (!ft_strncmp(cmd, "cd", 3))
		ft_cd(info, cmd_list->cmd);
	else if (!ft_strncmp(cmd, "export", 7))
		ft_export(info, cmd_list->cmd, cmd_list->outfd);
	else if (!ft_strncmp(cmd, "echo", 5))
		ft_echo(cmd_list->cmd, cmd_list->outfd);
	else if (!ft_strncmp(cmd, "pwd", 4))
		ft_pwd(*info, cmd_list->outfd);
	else if (!ft_strncmp(cmd, "unset", 6))
		ft_unset(&((*info)->env_list), cmd_list->cmd);
	else if (!ft_strncmp(cmd, "env", 4))
		ft_env((*info)->env_list, cmd_list->outfd);
	else if (!ft_strncmp(cmd, "exit", 5))
		ft_exit(*info, cmd_list->cmd);
	else
	{
		pids[0][cmd_num] = fork();
		if (pids[0][cmd_num] == -1)
			fork_err(info, cmd_list, *pids);
		else if (!pids[0][cmd_num])
			exec_nonbuiltin(*info, cmd_list);
	}
}

void	executor(t_info	**info, t_cmd_list *cmd_list)
{
	int 		cmdc;
	int			*pids;
	int			cmd_num;
	t_cmd_list	*tmp;

	cmdc = calc_cmds(cmd_list);
	pids = malloc(sizeof(int) * cmdc);
	if (!pids)
	{
		shell_err(info, cmd_list, "pids");
		return ;
	}
	ft_memset(pids, -1, sizeof(int) * cmdc);
	tmp = cmd_list;
	cmd_num = -1;
	while (++cmd_num < cmdc)
	{
		exec_cmd(info, tmp, &pids, cmd_num);
		if (tmp->infd != STDIN)
			close(tmp->infd);
		if (tmp->outfd != STDOUT)
			close(tmp->outfd);
		tmp = tmp->next;
	}
	end_exec(info, cmd_list, pids, cmdc);
}

	// {
	// 	ft_env((*info)->env_list, cmd_list->outfd);
	// 	ft_export(info, cmd_list->cmd, cmd_list->outfd);
	// 	ft_putendl_fd("", 1);
	// 	ft_env((*info)->env_list, cmd_list->outfd);
	// }

	// 	{
	// 	ft_env((*info)->env_list, cmd_list->outfd);
	// 	ft_unset(&((*info)->env_list), cmd_list->cmd);
	// 	ft_putendl_fd("", 1);
	// 	ft_env((*info)->env_list, cmd_list->outfd);
	// }