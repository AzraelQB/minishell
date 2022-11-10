/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 15:06:18 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(char *key, char *val, t_env_list **env)
{
	t_env_list	*new;

	if (!key || !val)
		return (errno);
	new = env_lstnew(key, val);
	if (!new)
		return (errno);
	env_lstadd_back(env, new);
	return (SUCCESS);
}

static void	export_key_and_val(char *arg, char *val, t_info **info)
{
	char	*key;

	key = ft_substr(arg, 0, (int)(val - arg));
	val = ft_strdup(val + 1);
	if (!key || !val)
	{
		perror("minishell: export: ");
		(*info)->exec_status = errno;
		return ;
	}
	env_add(key, val, &((*info)->env_list));
	free(key);
	free(val);
	return ;
}

static void	print_sorted_env(t_env_list *env, int fd)
{
	t_env_list	*iterator;
	t_env_list	*lowest;

	//printf("%p\n", env);
	env = env_lstcopy(env);
	//printf("%p\n", env);
	while (env)
	{
		iterator = env;
		lowest = env;
		while (iterator)
		{
			if (ft_strcmp(lowest->key, iterator->key) > 0)
				lowest = iterator;
			iterator = iterator->next;
		}
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(lowest->key, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(lowest->val, fd);
		env_lstremove(&env, lowest->key);
	}
}

void	ft_export(t_info **info, char **args, int fd)
{
	int		i;
	char	*val;

	if (!args[1])
	{
		//printf("%p\n", (*info)->env_list);
		print_sorted_env((*info)->env_list, fd);
		//printf("%p\n", (*info)->env_list);
		return ;
	}
	i = 0;
	while (args[++i])
	{
		val = ft_strchr(args[i], '=');
		if (!val)
			env_add(args[i], "", &((*info)->env_list));
		else
			export_key_and_val(args[i], val, info);
	}
}
//valid idents
