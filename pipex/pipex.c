/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:27:53 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/14 07:54:17 by aelidrys         ###   ########.fr       */
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

void	cmd_2(char *p, char **env, int *fd, char **args)
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
	print_error("exec2", NULL, args, path);
}

int	main(int a, char **p, char **env)
{
	int		fd[2];
	pid_t	pd;

	if (a != 5)
		print_error1("invalid number of argument\n", 1);
	chek_error(pipe(fd), 0);
	pd = fork();
	if (pd == -1)
		print_error1("fork", 0);
	if (pd == 0)
		cmd_1(p[1], env, fd, spl(p[2], ' ', 0));
	pd = fork();
	if (pd == -1)
		print_error1("fork", 0);
	if (pd == 0)
		cmd_2(p[4], env, fd, spl(p[3], ' ', 0));
	if (close(fd[1]) == -1 || close(fd[0]) == -1)
		print_error1("close", 0);
	while (wait(NULL) != -1)
		;
}
