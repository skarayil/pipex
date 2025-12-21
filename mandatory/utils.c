/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:44:00 by skarayil          #+#    #+#             */
/*   Updated: 2025/12/21 15:17:33 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*find_path(char *cmd, char **env_paths)
{
	char	*temp;
	char	*final_path;
	int		i;

	i = 0;
	while (env_paths && env_paths[i])
	{
		temp = ft_strjoin(env_paths[i], "/");
		final_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

void	ft_paths(t_pipex *p)
{
	int	i;

	i = 0;
	p->paths = NULL;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "PATH=", 5) == 0)
		{
			p->paths = ft_split(p->envp[i] + 5, ':');
			return ;
		}
		i++;
	}
}

void	ft_execute(char *argv, t_pipex *p)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		ft_free(cmd);
		ft_error("Command not found");
	}
	if (cmd[0][0] == '/' && access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = find_path(cmd[0], p->paths);
	if (!path)
	{
		ft_free(cmd);
		write(2, "Command not found\n", 18);
		exit(127);
	}
	if (execve(path, cmd, p->envp) == -1)
		ft_error("Execve Error");
}
