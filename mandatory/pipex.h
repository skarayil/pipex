/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:02:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/07 12:46:50 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../library/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_CMD "Command not found\n"
# define ERR_EMPTY "Empty command\n"
# define ERR_INFILE "Infile\n"
# define ERR_OUTFILE "Outfile\n"
# define ERR_EXECVE "Execve\n"
# define ERR_PIPE "Pipe\n"
# define ERR_FORK "Fork\n"
# define ERR_DUP "Dup2\n"

typedef struct s_files
{
	int		infile;
	int		outfile;
	int		tube[2];
}			t_files;

typedef struct s_pipex
{
	t_files	files;
	char	**envp;
	char	**paths;
	pid_t	child_1;
	pid_t	child_2;
}			t_pipex;

void		ft_eerror(char *str, t_pipex *p);
void		ft_execute(char *cmd_str, t_pipex *pipex);
void		ft_free(char **tab);
void		ft_paths(t_pipex *p);

#endif