/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:10:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/03 19:02:00 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd_pipe[2];
	int		pid;
	int		pid2;
	int		status;

	if (ac < 5)
		ppx_exit(-1, "Too few arguments", NULL, 2);
	else if (ac > 5)
		ppx_exit(-1, "Too many arguments", NULL, 2);
	ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);
	if (pid == 0)
		ppx_cmd1(av, env, fd_pipe);
	close(fd_pipe[1]);
	ppx_exit(pid2 = fork(), "Fork failed", fd_pipe, 1);
	if (pid2 == 0)
		ppx_cmd2(av, env, fd_pipe, 3);
	close(fd_pipe[0]);
	waitpid(pid, &status, 0);
	if (status == -1)
		exit(WEXITSTATUS(status));
	waitpid(pid2, &status, 0);
	if (status == -1)
		exit(WEXITSTATUS(status));
}
