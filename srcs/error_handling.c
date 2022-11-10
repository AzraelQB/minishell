/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:37:48 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:32:06 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_err(t_info	**info, t_cmd_list *cmd_list, int *pids)
{
	int	status;
	int	i;
	int	cmdc;

	i = -1;
	cmdc = calc_cmds(cmd_list);
	while (cmdc-- > 0)
	{
		if (pids[++i] != -1)
			kill(pids[i], SIGKILL);
	}
	free(pids);
	shell_err(info, cmd_list, "fork");
}

void	child_proc_err(char *err_location)//exec err
{
	ft_putstr_fd("Minishell: ", STDERR);
	if (err_location)
	{
		ft_putstr_fd(err_location, STDERR);
		ft_putstr_fd(": ", STDERR);	
	}
	if (errno)
		perror("");
	else
		ft_putendl_fd("an unexpected exception occured", STDERR);
	//exit(info->exec_status);
}

void	shell_err(t_info **info, t_cmd_list *cmd_list, char *err_location)
{
	(*info)->exec_status = errno;
	ft_putstr_fd("Minishell: ", STDERR);
	if (err_location)
	{
		ft_putstr_fd(err_location, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if ((*info)->exec_status)
		perror("");
	else
		ft_putstr_fd("an unexpected exception occured", STDERR);
	clear_iteration(*info, cmd_list);
}

void	clear_iteration(t_info *info, t_cmd_list *cmd_list)
{
	t_cmd_list	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		free_arr(tmp->cmd);
		if (tmp->infd != STDIN) close(tmp->infd);
		if (tmp->outfd != STDOUT) close(tmp->outfd);
		tmp = tmp->next;
	}
	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free(tmp);
	}
	if (info->heredocs)
	{
		while (*(info->heredocs))
		{
			unlink(*(info->heredocs));
			free(*(info->heredocs));//check if correct
			info->heredocs++;
		}
	}
}
