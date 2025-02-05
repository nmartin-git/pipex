/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:34:18 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/04 15:31:22 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ppx_exit(int err, const char *str, int *fd_pipe, int status)
{
	if (err == -1)
	{
		ft_printf_fd(2, "pipex : %s\n", str);
		if (fd_pipe)
			ppx_close(-1, fd_pipe, status, NULL);
		exit(status);
	}
}

void	ppx_close(int fd, int *fd_pipe, int err, char **cmd)
{
	if (cmd)
		ft_free_tab(cmd);
	if (fd != -1)
		close(fd);
	if (fd_pipe)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	exit(err);
}
