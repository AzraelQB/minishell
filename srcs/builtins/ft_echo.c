/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:46:31 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	ft_echo(char **args, int fd)
{
	int		i;
	int		n_option;

	i = 0;
	n_option = 0;
	if (calc_args(args) > 1)
	{
		while (args[++i] && !ft_strcmp(args[i], "-n"))
			n_option = 1;
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (n_option == 0)
		ft_putchar_fd('\n', fd);
}
