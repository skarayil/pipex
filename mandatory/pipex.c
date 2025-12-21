/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:00:49 by skarayil          #+#    #+#             */
/*   Updated: 2025/12/21 15:17:59 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	ft_child(t_pipex *p, int input_fd, int output_fd, char *cmd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("Dup2 Input Error");
		exit(1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("Dup2 Output Error");
		exit(1);
	}
	close(p->files.tube[0]);
	close(p->files.tube[1]);
	if (p->files.infile > -1)
		close(p->files.infile);
	if (p->files.outfile > -1)
		close(p->files.outfile);
	ft_execute(cmd, p);
}

static void	ft_infile(t_pipex *p, char *av[])
{
	p->files.infile = open(av[1], O_RDONLY);
	if (p->files.infile < 0)
	{
		perror(av[1]);
		close(p->files.tube[0]);
		close(p->files.tube[1]);
		ft_free(p->paths);
		exit(1);
	}
	ft_child(p, p->files.infile, p->files.tube[1], av[2]);
}

static void ft_outfile(t_pipex *p, char *av[])
{
	p->files.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->files.outfile < 0)
	{
		perror(av[4]);
		close(p->files.tube[0]);
		close(p->files.tube[1]);
		ft_free(p->paths);
		exit(1);
	}
	ft_child(p, p->files.tube[0], p->files.outfile, av[3]);
}

static void	ft_pipex(t_pipex *p, char **envp)
{
	p->envp = envp;
	p->files.infile = -1;
	p->files.outfile = -1;
	ft_paths(p);
	if (pipe(p->files.tube) == -1)
		ft_error("Pipe Error");
}

int	main(int argc, char *av[], char **envp)
{
	t_pipex	p;
	int		status;

	if (argc != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), 1);
	ft_pipex(&p, envp);
	p.child_1 = fork();
	if (p.child_1 == -1)
		ft_error("Fork Error");
	if (p.child_1 == 0)
		ft_infile(&p, av);
	p.child_2 = fork();
	if (p.child_2 == -1)
		ft_error("Fork Error");
	if (p.child_2 == 0)
		ft_outfile(&p, av);
	close(p.files.tube[0]);
	close(p.files.tube[1]);
	waitpid(p.child_1, NULL, 0);
	waitpid(p.child_2, &status, 0);
	ft_free(p.paths);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
