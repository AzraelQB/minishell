/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:37:48 by awooden           #+#    #+#             */
/*   Updated: 2022/09/18 19:38:55 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_info *info, t_cmd_list **cmd_list)
{
	int		pipefd[2];
	int		pipfd[2];
	int		fd1;
	int		fd2;
	char	**cmd;

	fd2 = open("test2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("echoo");
	cmd[1] = ft_strdup("aerg");
	cmd[2] = NULL;
	//pipe(pipefd);
	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
	// cmd = malloc(sizeof(char *) * 2);
	// cmd[0] = ft_strdup("cat");
	// cmd[1] = NULL;
	// cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, pipefd[0], 1));
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_info			*info;
	t_cmd_list		*cmd_list;
	int				pid;

	if (argc != 1)
		exit(ERROR);
	argv = NULL;
	cmd_list = NULL;
	info = create_t_info(env);
	while (!info->is_exit)
	{
		if (parser(info, &cmd_list))
			continue ;
		// while (cmd_list)
		// {
		// 	printf("%s ", cmd_list->cmd[0]);
		// 	printf("%d ", cmd_list->infd);
		// 	printf("%d \n", cmd_list->outfd);
		// 	cmd_list = cmd_list->next;
		// }
		executor(&info, cmd_list);
		printf("exec status is %d\n", info->exec_status);
		exit(info->exec_status);
	}
	// while (info->env_list)
	// {
	// 	printf("key is %s\n", info->env_list->key);
	// 	printf("value is %s\n", info->env_list->value);
	// 	info->env_list = info->env_list->next;
	// }
}


	// fd1 = open("test.txt", O_RDONLY);
	// fd2 = open("test2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	// cmd = malloc(sizeof(char *) * 2);
	// cmd[0] = ft_strdup("cat");
	// cmd[1] = NULL;
	// pipe(pipefd);
	// cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, fd1, pipefd[1]));
	// cmd = malloc(sizeof(char *) * 2);
	// cmd[0] = ft_strdup("cat");
	// cmd[1] = NULL;
	// pipe(pipfd);
	// cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, pipefd[0], pipfd[1]));
	// cmd = malloc(sizeof(char *) * 2);
	// cmd[0] = ft_strdup("cat");
	// cmd[1] = NULL;
	// cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, pipfd[0], fd2));




// int	parser(t_info *info, t_cmd_list **cmd_list)
// {
// 	int		pipefd[2];
// 	int		pipfd[2];
// 	int		fd1;
// 	int		fd2;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = ft_strdup("cd");
// 	cmd[1] = ft_strdup("/Dfe");
// 	cmd[2] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	return (0);
// }

// int	parser(t_info *info, t_cmd_list **cmd_list)
// {
// 	int		pipefd[2];
// 	int		pipfd[2];
// 	int		fd1;
// 	int		fd2;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = ft_strdup("env"); //pwd
// 	cmd[1] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	return (0);
// }

// int	parser(t_info *info, t_cmd_list **cmd_list)
// {
// 	int		pipefd[2];
// 	int		pipfd[2];
// 	int		fd1;
// 	int		fd2;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = ft_strdup("exit");
// 	cmd[1] = ft_strdup("-1000");
// 	cmd[2] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	return (0);
// }

// int	parser(t_info *info, t_cmd_list **cmd_list)
// {
// 	int		pipefd[2];
// 	int		pipfd[2];
// 	int		fd1;
// 	int		fd2;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 2);
// 	cmd[0] = ft_strdup("export");
// 	cmd[1] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = ft_strdup("export");
// 	cmd[1] = ft_strdup("ABOBA");
// 	cmd[2] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	cmd = malloc(sizeof(char *) * 2);
// 	cmd[0] = ft_strdup("export");
// 	cmd[1] = NULL;
// 	cmd_lstadd_back(cmd_list, cmd_lstnew(cmd, 0, 1));
// 	return (0);
// }