/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:26:06 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/08 09:22:34 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_eexit(char *msg, t_pipex *p)
{
	perror(msg);
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

static char	*ft_make(char *path, char *cmd)
{
	char	*res;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, path, len);
	ft_strlcat(res, "/", len);
	ft_strlcat(res, cmd, len);
	return (res);
}

void	ft_paths(t_pipex *p)
{
	int	i;

	i = 0;
	p->paths = NULL;
	if (!p->envp || !*p->envp)
	{
		p->paths = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
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

void	ft_execute(char *cmd, t_pipex *p)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_free(args);
		ft_eexit("Empty command", p);
	}
	if (ft_strchr(args[0], '/') && access(args[0], X_OK) == 0)
		execve(args[0], args, p->envp);
	i = -1;
	while (p->paths && p->paths[++i])
	{
		path = ft_make(p->paths[i], args[0]);
		if (access(path, X_OK) == 0)
			execve(path, args, p->envp);
		free(path);
	}
	ft_free(args);
	ft_free(p->paths);
	write(2, ERR_CMD, ft_strlen(ERR_CMD));
	exit(127);
}
