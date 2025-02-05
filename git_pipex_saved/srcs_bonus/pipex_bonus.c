/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:52:45 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/04 15:26:18 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ppx_cmd(char **av, char **env, int *fd_pipe, int i)
{
	char	**cmd;

	cmd = ft_split(av[i], ' ');
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	execve(ppx_envset(env, cmd[0]), cmd, env);
	ft_printf_fd(2, "pipex : command not found : %s\n", cmd[0]);
	ft_free_tab(cmd);
	exit(127);
}

void	ppx_multiplecmd(char **av, char **env, int *fd_pipe, int i)
{
	int	y;
	int	pid;

	y = ft_size_tab(av) - 3;
	if (i == y)
		close(fd_pipe[1]);
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);
	if (pid == 0 && i < y)
		ppx_cmd(av, env, fd_pipe, i);
	if (pid == 0 && i == y)
		ppx_cmd2(av, env, fd_pipe, i);
	if (i == y)
		close(fd_pipe[0]);
}

int	ppx_cmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == 0 && (s2[i] == 0 || (s2[i] == '\n' && s2[i + 1] == 0)))
		return (1);
	return (0);
}

void	ppx_here_doc(int ac, char **av, char **env, int *fd_pipe)
{
	int		pid;
	char	*str;

	str = NULL;
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);
	if (ac != 5)
		ppx_exit(-1, "here_doc : Too few arguments", fd_pipe, 2);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		while (!ppx_cmp(av[2], str))
		{
			if (str)
				ft_printf_fd(fd_pipe[1], "%s", str);
			free(str);
			ft_printf("pipe heredoc>");
			str = get_next_line(0);
		}
		free(str);
		close(fd_pipe[1]);
		exit(0);
	}
	close(fd_pipe[1]);
	waitpid(pid, 0, 0);
	ppx_cmd2(av, env, fd_pipe, 3);
}

int	main(int ac, char **av, char **env)
{
	int	fd_pipe[2];
	int	pid;
	int	i;

	i = 3;
	if (ac < 5)
		ppx_exit(-1, "Too few arguments", NULL, 2);
	ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
	if ((ft_strncmp(av[1], "here_doc", 9) == 0))
		ppx_here_doc(ac, av, env, fd_pipe);
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);
	if (pid == 0)
		ppx_cmd1(av, env, fd_pipe);
	while (av[i + 1])
		ppx_multiplecmd(av, env, fd_pipe, i++);
	while (wait(NULL) > 0)
		continue ;
}
