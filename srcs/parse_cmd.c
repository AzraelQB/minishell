/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:32:54 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:12:16 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_path(char **paths, char *cmd)
{
	char	*res;

	while (*paths)
	{
		res = ft_strjoin(*paths, cmd);
		if (!res)
		{
			child_proc_err("ft_strjoin paths cmd");
			exit(errno);
		}
		if (access(res, X_OK) == -1)
		{
			free(res);
			paths++;
		}
		else
			return (res);
	}
	child_proc_err("can't access the cmd");//can rewr
	exit(errno);
}

static char	**get_paths(t_env_list *env)
{
	char	**paths;

	while (env && ft_strncmp("PATH", env->key, 5))
		env = env->next;
	if (!env)
	{
		child_proc_err("env PATH");
		exit(errno);
	}
	paths = ft_split(env->val, ':');
	if (!paths)
	{
		child_proc_err("ft_split paths");
		exit(errno);
	}
	return (paths);
}

char	*make_cmd(t_env_list *env, char *cmd)
{
	char	*res;
	char	**paths;

	if (access(cmd, X_OK) == SUCCESS)
		return (cmd);
	cmd = ft_strjoin("/", cmd);//check malloc err reassigning cmd
	if (!cmd)
	{
		child_proc_err("ft_strjoin '/' cmd");
		exit(errno);
	}
	paths = get_paths(env);
	res = get_cmd_path(paths, cmd);
	free_arr(paths);
	free(cmd);
	return (res);
}
