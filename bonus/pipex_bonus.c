/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:26:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/08 09:22:44 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/get_next_line/get_next_line.h"
#include "pipex_bonus.h"
#include <fcntl.h>

static void	ft_process(char *cmd, t_pipex *p)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_eexit(ERR_PIPE, p);
	pid = fork();
	if (pid == -1)
		ft_eexit(ERR_FORK, p);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_eexit(ERR_DUP, p);
		close(fd[1]);
		ft_execute(cmd, p);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_eexit(ERR_DUP, p);
		close(fd[0]);
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	p;
	int		i;
	int		of_mode;

	if (ac < 5)
		return (write(2, ERR_ARGS, ft_strlen(ERR_ARGS)), 1);
	p.ac = ac;
	p.av = av;
	p.envp = envp;
	ft_paths(&p);
	ft_check(&p, &i, &of_mode);
	while (i < ac - 2)
		ft_process(av[i++], &p);
	p.io.outfile = open(av[ac - 1], of_mode, 0644);
	if (p.io.outfile == -1)
		ft_eexit(ERR_OUTFILE, &p);
	if (dup2(p.io.outfile, STDOUT_FILENO) == -1)
		ft_eexit(ERR_DUP, &p);
	close(p.io.outfile);
	ft_execute(av[ac - 2], &p);
	return (0);
}
