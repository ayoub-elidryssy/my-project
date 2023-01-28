/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touls1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:13:40 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/11 17:00:09 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	chek_error(int a, int b)
{
	if (a == -1 || b == -1)
	{
		perror("");
		exit(0);
	}
}

size_t	a_len(char *s)
{
	size_t	a;

	a = 0;
	while (s[a])
		a++;
	return (a);
}

char	*a_strjoin(char *s1, char *s2)
{
	char	*p;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	p = malloc(a_len(s1) + a_len(s2) + 2 * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[x])
	{
		p[x] = s1[x];
		x++;
	}
	p[x++] = '/';
	while (s2[y])
		p[x++] = s2[y++];
	p[x] = '\0';
	return (p);
}

int	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(0);
	}
	return (pid);
}

void	print_fd(int fd, char *p)
{
	while (p && *p)
		write(fd, p++, 1);
}
