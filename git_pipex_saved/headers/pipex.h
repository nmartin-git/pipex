/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:47:35 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/04 18:07:06 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"

void	ppx_exit(int err, const char *str, int *fd_pipe, int status);
void	ppx_close(int fd, int *fd_pipe, int err, char **cmd);

void	ppx_cmd1(char **av, char **env, int *fd_pipe);
void	ppx_cmd2(char **av, char **env, int *fd_pipe, int i);
char	*ppx_envset(char **env, char *cmd);
int		ppx_set_fd(char *f, int *fd_pipe);
int		ppx_cmd2_fd(char **av, int *fd_pipe, int i);

#endif
