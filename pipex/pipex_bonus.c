/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:14:16 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/14 08:02:34 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_1(char *p, char **env, int *fd, char **args)
{
	int		fd0;
	char	*path;

	path = lpth(env, args[0], -1);
	fd0 = open(p, O_RDONLY);
	if (fd0 == -1)
		print_error(p, NULL, args, path);
	if (!a_dupx(fd, STDOUT_FILENO, fd0, STDIN_FILENO))
		print_error("", NULL, args, path);
	if (!path)
		print_error(args[0], " :command not found\n", args, path);
	execve(path, args, env);
	print_error("exec1", NULL, args, path);
}

void	cmd_x(int *fd, char **env, char **args)
{
	char	*path;

	path = lpth(env, args[0], -1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		print_error("dup2", NULL, args, path);
	if (close(fd[1]) || close(fd[0]))
		print_error("close", NULL, args, path);
	if (!path)
		print_error(args[0], " :command not found\n", args, path);
	execve(path, args, env);
	print_error("execx", NULL, args, path);
}

void	cmd(char *p, char **env, int *fd, char **args)
{
	int		fd1;
	char	*path;

	path = lpth(env, args[0], -1);
	if (!path)
		print_error(args[0], " :command not found\n", args, path);
	fd1 = open(p, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd1 == -1)
		print_error(p, NULL, args, path);
	if (!a_dupx(fd, STDIN_FILENO, fd1, STDOUT_FILENO))
		print_error("", NULL, args, path);
	execve(path, args, env);
	print_error("execn", NULL, args, path);
}

void	here_doc(int a, char **p, char **env)
{
	int	fd[2];

	if (a != 6)
		print_error1("invalid number of argument\n", 1);
	chek_error(pipe(fd), 0);
	if (ft_fork() == 0)
		cm_1(fd, p[2], env, spl(p[3], ' ', 0));
	wait(NULL);
	if (close(fd[1]) == -1)
		print_error1("close", 1);
	if (ft_fork() == 0)
		cm_2(fd, p[5], env, spl(p[4], ' ', 0));
	wait(NULL);
	exit(0);
}

int	main(int a, char **p, char **env)
{
	int	fd[2];
	int	n;

	n = 0;
	if (ft_strcmp(p[1], "here_doc", 0))
		here_doc(a, p, env);
	if (a < 5)
		print_error1("invalid number of argument\n", 1);
	chek_error(pipe(fd), 0);
	if (ft_fork() == 0)
		cmd_1(p[1], env, fd, spl(p[2], ' ', 0));
	chek_error(dup2(fd[0], STDIN_FILENO), close(fd[1]));
	while (++n + 4 < a)
	{
		chek_error(pipe(fd), 0);
		if (ft_fork() == 0)
			cmd_x(fd, env, spl(p[n + 2], ' ', 0));
		chek_error(dup2(fd[0], STDIN_FILENO), close(fd[1]));
	}
	if (ft_fork() == 0)
		cmd(p[a - 1], env, fd, spl(p[a - 2], ' ', 0));
	clos_and_wait(fd);
}
