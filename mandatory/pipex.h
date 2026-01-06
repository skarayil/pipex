/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:02:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/06 16:05:20 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>

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