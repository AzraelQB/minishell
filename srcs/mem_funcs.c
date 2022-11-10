/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:50:20 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:11:17 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*create_t_info(char	**env)
{
	t_info	*res;
	char	*key;
	char	*value;
	int		i;

	res = malloc(sizeof(t_info));
	if (!res)
		exit(ERROR);//mb rewr to return
	ft_memset(res, 0, sizeof(t_info));//move higher to guarantee nullification
	res->env = env;
	i = -1;
	while (env[++i])
	{
		value = env[i];
		while (*value != '=')
			value++;
		key = ft_substr(env[i], 0, value - env[i]);
		if (!key)
			exit(ERROR);
		++value;
		env_lstadd_back(&(res->env_list), env_lstnew(key, value));//malloc err
		free(key);
	}
	return (res);
}
