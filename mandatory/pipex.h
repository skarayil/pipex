/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 09:05:38 by skarayil          #+#    #+#             */
/*   Updated: 2025/12/21 09:26:58 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


typedef struct s_pipex
{
	int tube[2];
	int infile;
	int outfile;
	char **paths;
	char **cmd_args;
	char *cmd_path;
	pid_t	child_1;
	pid_t	child_2;
}			t_pipex;


void		ft_infile(t_pipex pipex, char **argv, char **envp);
void		ft_outfile(t_pipex pipex, char **argv, char **envp);
void		error_msg(char *msg);
void		execute(char *cmd, char **envp);
char		*find_path(char *cmd, char **envp);

#endif