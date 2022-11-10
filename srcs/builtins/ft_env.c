/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:16:52 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env_list *env_list, int fd)
{
	while (env_list)
	{
		ft_putstr_fd(env_list->key, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(env_list->val, fd);
		env_list = env_list->next;
	}
}
