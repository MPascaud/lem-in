/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:44:23 by mpascaud          #+#    #+#             */
/*   Updated: 2018/04/18 20:30:05 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEM_IN_H

# define LEM_IN_H
# define BUFF_SIZE 65
# define MAX_FD 4865

# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>



int				get_next_line(const int fd, char **line);
char			*ft_strnew(size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_isdigit(int c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_strcmp(const char *s1, const char *s2);


typedef struct	s_filist
{
	char	*line;
	struct	s_filist	*previous;
	struct	s_filist	*next;
}				t_filist;

typedef struct	s_roomlist
{
	char				**beftunnels;
	char				**tunnels;
	int					place;
	char				*name;
	struct	s_roomlist	*previous;
	struct	s_roomlist	*next;
}				t_roomlist;

#endif
















