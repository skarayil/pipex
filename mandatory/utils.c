/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 09:05:35 by skarayil          #+#    #+#             */
/*   Updated: 2025/12/21 09:23:47 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_part;
	char	*full_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

void	execute(char *cmd, char **envp)
{
	char **cmd_args;
	char *path;

	cmd_args = ft_split(cmd, ' ');

	path = find_path(cmd_args[0], envp);

	if (!path)
	{
		write(2, "Command not found: ", 19);
		write(2, cmd_args[0], ft_strlen(cmd_args[0]));
		write(2, "\n", 1);
		exit(127);
	}

	if (execve(path, cmd_args, envp) == -1)
		error_msg("Execve Error");
}