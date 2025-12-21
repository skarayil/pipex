/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 09:05:41 by skarayil          #+#    #+#             */
/*   Updated: 2025/12/21 09:24:38 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *msg)
{
	perror(msg);
	exit(1);
}

void	child_one(t_pipex pipex, char *av[], char **envp)
{
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile == -1)
		error_msg("Infile Error");
	dup2(pipex.infile, STDIN_FILENO);
	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	close(pipex.infile);
	execute(av[2], envp);
}

void	child_two(t_pipex pipex, char *av[], char **envp)
{
	pipex.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.outfile == -1)
		error_msg("Outfile Error");
	dup2(pipex.tube[0], STDIN_FILENO);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.tube[1]);
	close(pipex.outfile);
	close(pipex.tube[0]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	if (ac != 5)
		return (write(2, "Args Error\n", 11), 1);

	if (pipe(pipex.tube) == -1)
		error_msg("Pipe Error");

	pipex.child_1 = fork();
	if (pipex.child_1 == 0)
		child_one(pipex, av, envp);

	pipex.child_2 = fork();
	if (pipex.child_2 == 0)
		child_two(pipex, av, envp);

	close(pipex.tube[0]);
	close(pipex.tube[1]);

	waitpid(pipex.child_1, NULL, 0);
	waitpid(pipex.child_2, NULL, 0);

	return (0);
}