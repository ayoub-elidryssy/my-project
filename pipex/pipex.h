/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:14:12 by aelidrys          #+#    #+#             */
/*   Updated: 2023/01/11 15:31:31 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>
# include "get_next_line.h"

void	print_error(char *p, char *s, char **p1, char *p2);
void	cm_1(int *fd, char *lmtr, char **env, char **args);
void	cm_2(int *fd, char *p, char **env, char **args);
char	*lpth(char **d, char	*cmd, int n);
int		a_dupx(int *fd, int x, int a, int b);
int		ft_strcmp(char *s, char *p, int x);
void	print_error1(char *p1, int x);
char	*a_strjoin(char*s1, char *s2);
char	**spl(char*s, char c, int n);
void	print_fd(int fd, char *p);
int		copy_to_file(char *lmtr);
void	chek_error(int a, int b);
void	clos_and_wait(int *fd);
int		ft_fork(void);

#endif