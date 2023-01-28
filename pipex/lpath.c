/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 07:47:02 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/14 06:55:51 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	path_indix(char **p)
{
	int		x;
	int		y;
	char	*s;

	s = "PATH=";
	x = 0;
	while (p[x])
	{
		y = 0;
		while (p[x][y] == s[y])
			y++;
		if (s[y] == '\0')
			return (x);
		x++;
	}
	return (0);
}

char	*lpth(char **d, char *cmd, int n)
{
	char	*path;
	char	**s;

	if (!d || !cmd)
		return (0);
	if (!access(cmd, F_OK))
		return (cmd);
	s = spl(d[path_indix(d)], ':', 1);
	while (s && s[++n])
	{
		path = a_strjoin(s[n], cmd);
		if (access(path, F_OK) == -1)
			free(path);
		else
			break ;
	}
	n = 0;
	while (s[n])
		free(s[n++]);
	free(s);
	if (access(path, F_OK) == -1)
		return (0);
	return (path);
}
