/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_touls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:04:13 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/14 08:07:31 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	copy_to_file(char *lmtr)
{
	char	*p;
	int		fd1;

	fd1 = open("here_doc_text", O_CREAT | O_RDWR, 0777);
	if (fd1 == -1)
		return (-1);
	while (1)
	{
		p = get_next_line(0);
		if (ft_strcmp(p, lmtr, 1) == 1)
		{
			free(p);
			return (fd1);
		}
		print_fd(fd1, p);
		free(p);
	}
	return (fd1);
}

void	cm_1(int *fd, char *p, char **env, char **args)
{
	int		fd0;
	char	*path;

	path = lpth(env, args[0], -1);
	if (copy_to_file(p) == -1)
		print_error(p, NULL, args, path);
	fd0 = open("here_doc_text", O_RDONLY);
	if (fd0 == -1)
		print_error(p, NULL, args, path);
	if (!a_dupx(fd, STDOUT_FILENO, fd0, STDIN_FILENO))
		print_error("", NULL, args, path);
	if (unlink("here_doc_text") == -1 || close(fd0))
		print_error("", NULL, args, path);
	if (!path)
		print_error(args[0], " :command not found\n", args, path);
	execve(path, args, env);
	print_error("exec1", NULL, args, path);
}

void	cm_2(int *fd, char *p, char **env, char **args)
{
	int		fd1;
	char	*path;

	path = lpth(env, args[0], -1);
	fd1 = open(p, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd1 == -1)
		print_error(p, NULL, args, path);
	if (!a_dupx(fd, STDIN_FILENO, fd1, STDOUT_FILENO))
		print_error("", NULL, args, path);
	if (!path)
		print_error(args[0], " :command not found\n", args, path);
	execve(path, args, env);
	print_error("exec2", NULL, args, path);
}
