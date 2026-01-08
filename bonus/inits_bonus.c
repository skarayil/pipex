/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:19:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/08 09:24:46 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/get_next_line/get_next_line.h"
#include "pipex_bonus.h"
#include <fcntl.h>

void	ft_heredoc(t_pipex *p)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_eexit(ERR_PIPE, p);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, p->io.limiter, ft_strlen(p->io.limiter)) == 0
			&& line[ft_strlen(p->io.limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_eexit(ERR_DUP, p);
	close(fd[0]);
}

static void	ft_open_infile(t_pipex *p)
{
	p->io.infile = open(p->av[1], O_RDONLY);
	if (p->io.infile == -1)
		ft_eexit(ERR_INFILE, p);
	if (dup2(p->io.infile, STDIN_FILENO) == -1)
		ft_eexit(ERR_DUP, p);
	close(p->io.infile);
}

void	ft_check(t_pipex *p, int *i, int *mode)
{
	if (ft_strncmp(p->av[1], "here_doc", 8) == 0)
	{
		if (p->ac < 6)
		{
			write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
			ft_free(p->paths);
			exit(1);
		}
		p->io.heredoc = 1;
		p->io.limiter = p->av[2];
		*i = 3;
		*mode = O_WRONLY | O_CREAT | O_APPEND;
		ft_heredoc(p);
	}
	else
	{
		p->io.heredoc = 0;
		*i = 2;
		*mode = O_WRONLY | O_CREAT | O_TRUNC;
		ft_open_infile(p);
	}
}
