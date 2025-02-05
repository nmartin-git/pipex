/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:52:25 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/04 18:11:38 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ppx_cmd2_fd(char **av, int *fd_pipe, int i)
{
	int	fd;

	if (access(av[i + 1], F_OK) == 0 && access(av[i + 1], W_OK) == -1)
	{
		ft_printf_fd(2, "%s : %s\n", strerror(13), av[i + 1]);
		ppx_close(-1, fd_pipe, 13, NULL);
	}
	fd = open(av[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf_fd(2, "pipex : Failed oppening file : %s\n", av[i + 1]);
		ppx_close(-1, fd_pipe, 1, NULL);
	}
	return (fd);
}

int	ppx_set_fd(char *f, int *fd_pipe)
{
	int	fd;

	if (access(f, F_OK) == -1)
	{
		ft_printf_fd(2, "pipex : Cannot access '%s' : %s\n", f, strerror(2));
		ppx_close(-1, fd_pipe, 2, NULL);
	}
	if (access(f, R_OK) == -1)
	{
		ft_printf_fd(2, "%s : %s\n", strerror(13), f);
		ppx_close(-1, fd_pipe, 13, NULL);
	}
	fd = open(f, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "pipex : Failed oppening file : %s\n", f);
		ppx_close(-1, fd_pipe, 1, NULL);
	}
	return (fd);
}

char	*ppx_envset(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while (env[i] && strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i] || !cmd)
		return (cmd);
	path = ft_split(&env[i][5], ':');
	if (!path)
		return (cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_tab(path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_tab(path), cmd);
}

void	ppx_cmd1(char **av, char **env, int *fd_pipe)
{
	int		fd;
	char	**cmd;
	char	*env_set;

	fd = ppx_set_fd(av[1], fd_pipe);
	cmd = ppx_setcmd(ft_split(av[2], ' '), ft_strdup(av[1]), fd, fd_pipe);
	close(fd_pipe[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	env_set = ppx_envset(env, cmd[0]);
	execve(env_set, cmd, env);
	ft_printf_fd(2, "pipex : command not found : %s\n", cmd[0]);
	if (env_set != cmd[0])
		free(env_set);
	ft_free_tab(cmd);
	exit(127);
}

void	ppx_cmd2(char **av, char **env, int *fd_pipe, int i)
{
	char	**cmd;
	char	*env_set;
	int		fd;

	fd = ppx_cmd2_fd(av, fd_pipe, i);
	cmd = ft_split(av[i], ' ');
	env_set = ppx_envset(env, cmd[0]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(env_set, cmd, env);
	ft_printf_fd(2, "pipex : command not found : %s\n", cmd[0]);
	if (env_set != cmd[0])
		free(env_set);
	return (ft_free_tab(cmd), exit(127));
}
