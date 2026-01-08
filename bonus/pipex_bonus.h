/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:25:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/01/08 09:22:41 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../library/libft/libft.h"

# define ERR_ARGS "Invalid number of arguments.\n"
# define ERR_CMD "Command not found\n"
# define ERR_PIPE "Pipe error\n"
# define ERR_FORK "Fork error\n"
# define ERR_DUP "Dup2 error\n"
# define ERR_INFILE "Infile error\n"
# define ERR_OUTFILE "Outfile error\n"

typedef struct s_io
{
	int		infile;
	int		outfile;
	int		heredoc;
	char	*limiter;
}			t_io;

typedef struct s_pipex
{
	t_io	io;
	char	**paths;
	char	**envp;
	char	**av;
	int		ac;
}			t_pipex;

void		ft_eexit(char *msg, t_pipex *p);
void		ft_free(char **tab);
void		ft_paths(t_pipex *p);
void		ft_execute(char *cmd, t_pipex *p);
void		ft_heredoc(t_pipex *p);
void		ft_check(t_pipex *p, int *i, int *mode);

#endif