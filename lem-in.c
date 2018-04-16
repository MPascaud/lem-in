/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/04/16 17:50:12 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"



t_filist	*ft_filstnew(char *tmp, t_filist *link)
{
	t_filist	*nextlink;
	char		*str;

	if (!(nextlink = (t_filist*)malloc(sizeof(t_filist))))
		return (NULL);
	nextlink->previous = link;
	str = ft_strnew(ft_strlen(tmp));
	nextlink->line = ft_strcpy(str, tmp);
	nextlink->next = NULL;
	return (nextlink);
}


void	ft_show_filist(t_filist *filist)
{
	filist = filist->next;
	while (filist != NULL)
	{
		printf("%s\n", filist->line);
		filist = filist->next;
	}
}

t_roomlist	*ft_roomlstnew(t_roomlist *roomlist)
{
	t_roomlist	*nextlink;

	if (!(nextlink = (t_roomlist*)malloc(sizeof(t_roomlist))))
		return (NULL);
	nextlink->previous = roomlist;
	nextlink->next = NULL;
	return (nextlink);
}

int		ft_this_is_new_room(t_filist *filist)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (filist->line == NULL)
		return (0);
	while ((filist->line)[i] != '\0')
	{

		i++;
	}
	i--;
	//printf("i = %d\n", i);
	while (ft_isdigit((filist->line)[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	//printf("i = %d\n", i);
	if ((filist->line)[i] == ' ' && (filist->line)[0] != '#')
	{
		return (1);
	}
	return (0);
}

void	ft_cpyname(t_filist *filist, t_roomlist *roomlist)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
		i++;
	//printf("i = %d\n", i);
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
//	printf("i = %d\n", i);
	roomlist->name = ft_strnew(i + 1);
	while (j <= i)
	{
		(roomlist->name)[j] = (filist->line)[j];
		j++;
	}

//	str = ft_strnew(ft_strlen(filist->line));
//	roomlist
}


void	ft_name(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	while (filist != NULL)
	{
		if (ft_this_is_new_room(filist) == 1)
		{
			roomlist->next = ft_roomlstnew(roomlist);
			roomlist = roomlist->next;
			ft_cpyname(filist, roomlist);
			//printf("blop\n");
		}
		filist = filist->next;
	}
}

void	ft_show_roomlist(t_roomlist *roomlist)
{
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		printf("%s\n", roomlist->name);
		roomlist = roomlist->next;
	}
}

int		main(void)
{
	char		*tmp;
	t_filist	*filist;
	t_filist	*filistart;
	t_roomlist	*roomlist;
	t_roomlist	*roomlistart;

	filist = (t_filist*)malloc(sizeof(t_filist));
	filist->previous = NULL;
	filist->line = NULL;
	filist->next = NULL;
	filistart = filist;
	while (1)
	{
		while (get_next_line(0, &tmp))
		{
			filist->next = ft_filstnew(tmp, filist);
			filist = filist->next;
			//printf("%s\n", tmp);
		}
		break ;
	}
	ft_show_filist(filistart);
	
	
	roomlist = (t_roomlist*)malloc(sizeof(t_roomlist));
	roomlist->previous = NULL;
	roomlist->place = 0;
	roomlist->name = NULL;
	roomlist->previous = NULL;
	roomlist->next = NULL;
	ft_name(filistart, roomlist);


	ft_show_roomlist(roomlist);




















	return (0);
}
