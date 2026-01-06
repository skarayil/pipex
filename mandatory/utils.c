/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:44:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/06 16:09:05 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	ft_eerror(char *str, t_pipex *p)
{
	perror(str);
	if (p && p->paths)
		ft_free(p->paths);
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

static char	*ft_build_path(char *path, char *cmd)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, cmd);
	free(temp);
	return (res);
}

void	ft_paths(t_pipex *p)
{
	int	i;

	i = 0;
	p->paths = NULL;
	if (!p->envp || !*p->envp)
	{
		p->paths = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/homebrew/bin",
				':');
		return ;
	}
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
	int		i;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		ft_free(cmd);
		ft_eerror("Command empty", p);
	}
	if (ft_strchr(cmd[0], '/') && execve(cmd[0], cmd, p->envp) == -1)
		(ft_free(cmd), ft_eerror("Execve Error", p));
	i = -1;
	while (p->paths && p->paths[++i])
	{
		path = ft_build_path(p->paths[i], cmd[0]);
		execve(path, cmd, p->envp);
		free(path);
	}
	ft_free(cmd);
	if (p->paths)
		ft_free(p->paths);
	(write(2, "Command not found\n", 18), exit(127));
}
