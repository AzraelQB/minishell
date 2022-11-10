/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:46:54 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_info *info, char **args)
{
	int					minus;
	unsigned long long	exit_arg;

	minus = 0;
	ft_putendl_fd("exit\n", STDOUT);
	if (!args[1])
		exit(info->exec_status % 256);
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR);
		return ;
	}
	exit_arg = ft_atoull(args[1], &minus);
	if (!ft_isnumeric(args[1]) || !minus && exit_arg > __LONG_LONG_MAX__ || \
		minus && exit_arg - 1 > __LONG_LONG_MAX__)
	{
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		exit(255);
	}
	if (minus)
		exit((int)(-exit_arg % 256));
	else
		exit((int)(exit_arg % 256));
}//needs tests
