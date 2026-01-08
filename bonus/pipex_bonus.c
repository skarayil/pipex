/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:26:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/08 09:32:04 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/get_next_line/get_next_line.h"
#include "pipex_bonus.h"
#include <fcntl.h>
#include <sys/wait.h>

static void	ft_last(char *cmd, t_pipex *p, int mode)
{
	pid_t	pid;

	p->io.outfile = open(p->av[p->ac - 1], mode, 0644);
	if (p->io.outfile == -1)
		ft_eexit(ERR_OUTFILE, p);
	pid = fork();
	if (pid == -1)
		ft_eexit(ERR_FORK, p);
	if (pid == 0)
	{
		if (dup2(p->io.outfile, STDOUT_FILENO) == -1)
			ft_eexit(ERR_DUP, p);
		close(p->io.outfile);
		ft_execute(cmd, p);
	}
	close(p->io.outfile);
	close(STDIN_FILENO);
}

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
	int		mode;
	int		count;

	if (ac < 5)
		return (write(2, ERR_ARGS, ft_strlen(ERR_ARGS)), 1);
	p.ac = ac;
	p.av = av;
	p.envp = envp;
	ft_paths(&p);
	ft_check(&p, &i, &mode);
	count = ac - 1 - i;
	while (i < ac - 2)
		ft_process(av[i++], &p);
	ft_last(av[ac - 2], &p, mode);
	while (count-- >= 0)
		wait(NULL);
	ft_free(p.paths);
	return (0);
}
