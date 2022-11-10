/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:46:41 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_env_list **env)
{
	char		cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("minishell: cd: ");
		return (errno);
	}
	env_lstremove(env, "OLDPWD");
	if (env_add("OLDPWD", cwd, env))
	{
		perror("minishell: cd: ");
		return (errno);
	}
	return (SUCCESS);
}

static int	change_dir(char *path, t_env_list **env)
{
	int	cd_status;
	char		cwd[PATH_MAX];

	//getcwd(cwd, PATH_MAX);
	//printf("%s\n", cwd);
	if (chdir(path) != SUCCESS)
	{
		cd_status = errno;
		ft_putstr_fd("minishell: cd: ", STDERR);
		perror(path);
	}
	else
		cd_status = update_oldpwd(env);
	//getcwd(cwd, PATH_MAX);
	//printf("%s\n", cwd);
	return (cd_status);
}


static char	*get_env_path(t_env_list *env, const char *var)
{
	char	*oldpwd;

	while (env)
	{
		if (!ft_strncmp(env->key, var, ft_strlen(var)))
		{
			oldpwd = ft_strdup(env->val);
			if (!oldpwd)
				return (NULL);
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	get_path(t_env_list *env, char **path, int option)
{
	if (option == 0)
	{
		*path = get_env_path(env, "HOME");
		if (!*path)
			ft_putstr_fd("minishell : cd: HOME not set\n", STDERR);
	}
	else if (option == 1)
	{
		*path = get_env_path(env, "OLDPWD");
		if (!*path)
			ft_putstr_fd("minishell : cd: OLDPWD not set\n", STDERR);
	}
	if (!*path)
		return (ERROR);
	return (SUCCESS);
}

void	ft_cd(t_info **info, char **args)
{
	int		cd_status;
	char	*path;

	cd_status = SUCCESS;
	path = args[1];
	if (!args[1] || (!ft_strcmp(args[1], "~") && !args[2]))
		cd_status = get_path((*info)->env_list, &path, 0);
	else if (!ft_strcmp(args[1], "-") && !args[2])
		cd_status = get_path((*info)->env_list, &path, 1);
	else if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		cd_status = ERROR;
	}
	if (cd_status == SUCCESS)
		cd_status = change_dir(path, &((*info)->env_list));
	(*info)->exec_status = cd_status;
}//later can rewr **
