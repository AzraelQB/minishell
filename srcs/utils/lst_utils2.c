/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 14:38:50 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*env_lstcopy(t_env_list *alist)
{
	t_env_list	*res;

	res = NULL;
	while (alist)
	{
		env_lstadd_back(&res, env_lstnew(alist->key, alist->val));
		alist = alist->next;
	}
	return (res);
}
