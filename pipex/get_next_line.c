/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:30:05 by aelidrys          #+#    #+#             */
/*   Updated: 2022/11/18 17:00:47 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	chek_line(char *p)
{
	size_t	x;

	x = 0;
	if (!p)
		return (0);
	while (p[x])
		if (p[x++] == '\n')
			return (x);
	return (0);
}

char	*ft_free(char *s, char *d)
{
	if (s)
		free(s);
	if (d)
		free(d);
	return (NULL);
}

char	*read_line(int fd, char *d)
{
	char	*s;
	int		x;

	s = ft_calloc(BUFFER_SIZE + 1, 1);
	while (chek_line(s) == 0)
	{
		x = read(fd, s, BUFFER_SIZE);
		if (x == -1)
			return (ft_free(s, d));
		if (x == 0)
			break ;
		s[x] = '\0';
		d = ft_strjoin(d, s, x);
	}
	free(s);
	return (d);
}

char	*get_next_line(int fd)
{
	static char	*p;
	char		*d;

	d = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!chek_line(p))
	{
		p = read_line(fd, p);
		if (!p)
			return (NULL);
		if (chek_line(p) == 0)
			d = ft_strdup(p, ft_strlen(p), &p);
		else
		{
			d = ft_strdup1(p, chek_line(p), 0);
			p = ft_strdup1(p, ft_strlen(p + chek_line(p)), chek_line(p));
		}
	}
	else if (p && chek_line(p))
	{
		d = ft_strdup1(p, chek_line(p), 0);
		p = ft_strdup1(p, ft_strlen(p + chek_line(p)), chek_line(p));
	}
	return (d);
}
