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

char	**ppx_setcmd(char **cmd, char *f, int fd, int *fdp)
{
	int		size_tab;
	char	**cmd_p;

	size_tab = 0;
	if (!cmd || !f)
		return (free(f), ppx_close(fd, fdp, 1, cmd), NULL);
	while (cmd[size_tab])
		size_tab++;
	cmd_p = malloc(sizeof(char *) * (size_tab + 2));
	if (!cmd_p)
		return (free(f), ppx_close(fd, fdp, 1, cmd), NULL);
	size_tab = 0;
	while (cmd[size_tab])
	{
		cmd_p[size_tab] = ft_strdup(cmd[size_tab]);
		if (!cmd_p[size_tab])
		{
			ft_free_tab(cmd);
			return (free(f), ppx_close(fd, fdp, 1, cmd_p), NULL);
		}
		size_tab++;
	}
	cmd_p[size_tab++] = f;
	cmd_p[size_tab] = NULL;
	return (ft_free_tab(cmd), cmd_p);
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
