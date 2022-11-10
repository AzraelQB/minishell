/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:56:04 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 14:38:37 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*env_lstnew(char *key, char *val)
{
	t_env_list	*elem;

	elem = malloc(sizeof(t_env_list));
	if (elem == NULL)
		return (NULL);
	elem->key = ft_strdup(key);
	elem->val = ft_strdup(val);
	if (!elem->key || !elem->val)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

void	env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd_list	*cmd_lstnew(char **value, int in, int out)
{
	t_cmd_list	*elem;

	elem = malloc(sizeof(t_cmd_list));
	if (elem == NULL)
		return (NULL);
	elem->cmd = value;
	elem->next = NULL;
	elem->infd = in;
	elem->outfd = out;
	return (elem);
}

void	cmd_lstadd_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	env_lstremove(t_env_list **env, char *key)
{
	t_env_list	*tmp;
	t_env_list	*to_free;

	if (!env || !*env)
		return ;
	if (!ft_strcmp((*env)->key, key))
	{
		free((*env)->key);
		free((*env)->val);
		tmp = (*env)->next;
		free(*env);
		*env = tmp;
		return ;
	}
	tmp = *env;
	while (tmp->next && ft_strcmp(tmp->next->key, key))
		tmp = tmp->next;
	if (!tmp->next)
		return ;
	to_free = tmp->next;
	tmp->next = tmp->next->next;
	free(to_free->key);
	free(to_free->val);
	free(to_free);
}

// int	ft_lstsize(t_list *lst)
// {
// 	int		res;
// 	t_list	*tmp;

// 	res = 0;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		res++;
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }

// t_list	*ft_lstlast(t_list *lst)
// {
// 	t_list	*tmp;

// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->next == NULL)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	ft_lstfree(t_list **alist)
// {
// 	t_list	*cur;

// 	if (!(*alist))
// 		return ;
// 	while ((*alist)->next)
// 	{
// 		cur = (*alist)->next;
// 		free((*alist));
// 		(*alist) = cur;
// 	}
// 	free(*alist);
// }