/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:34:20 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/14 06:48:40 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *p, char *s, char **p1, char *p2)
{
	int	x;

	x = 0;
	if (!s)
		perror(p);
	else
	{
		while (p && *p)
			write(2, p++, 1);
		while (s && *s)
			write(2, s++, 1);
	}
	while (p1 && p1[x])
		free(p1[x++]);
	free(p1);
	free(p2);
	exit(0);
}

void	print_error1(char *p1, int x)
{
	if (x)
		while (p1 && *p1)
			write (2, p1++, 1);
	if (!x)
		perror(p1);
	exit(0);
}

void	clos_and_wait(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) != -1)
		;
}

int	a_dupx(int *fd, int x, int a, int b)
{
	if (dup2(fd[x], x) == -1 || dup2(a, b) == -1)
		return (0);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		return (0);
	return (1);
}

int	ft_strcmp(char *s, char *p, int x)
{
	int	n;

	n = 0;
	if (!s || !p)
		return (0);
	while (s[n] && p[n])
	{
		if (s[n] != p[n])
			return (0);
		n++;
	}
	if (x && s[n] == '\n' && p[n] == '\0')
		return (1);
	else if (s[n] == p[n])
		return (1);
	return (0);
}
