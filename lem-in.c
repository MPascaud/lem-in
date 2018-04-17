/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/04/17 18:09:43 by mpascaud         ###   ########.fr       */
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
	nextlink->place = -1;
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
		printf("%d\n", roomlist->place);
		roomlist = roomlist->next;
	}
}


int		ft_disizit(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((roomlist->name)[i] != (filist->line)[i])
		{
			return (0);
		}
		i++;
	}
	if (filist->line[i] != ' ' || ft_isdigit(filist->line[i + 1]) == 0)
		return (0);
	return (1);
}


void	ft_place_start(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##start"))
		{
			//printf("COUCOU\n");
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = 0;
					return ;
				}
				roomlist = roomlist->next;
			}

		}
		filist = filist->next;
	}

}

//liste des tubes avec un 'pris en compte'
//tant que tous les tubes ne sont pas pris en compte
//a chaque ligne : si place du 2e = -1 et que place du 1er != -1, place du 2e = place du 1er + 1
//tour supplementaire sur liste tubes pour calculer taille du malloc du premier(roomlist->tunnel)
//refaire un tour pour joindre roomlist: les 2e sont ajoutes a la liste du 1er
//


int		ft_disiz_tunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;

	there_is_tunnel = 0;
	i = 0;

	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
			there_is_tunnel = 1;
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[i] || filist->line[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}


void	ft_place(t_filist *filist, t_roomlist *roomlist)
{
	int		i;
	int		tunnbr;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	tunnbr = 0;
	filist = filist->next;
	filistart = filist;
	roomlist = roomlist->next;
	roomlistart = roomlist;
	while (filist != NULL)
	{
		while ((filist->line)[i] != '\0')
		{
			if ((filist->line)[i] == '-' && (filist->line)[0] != '#')
			{
				tunnbr++;
				break ;
			}
			i++;
		}
		filist = filist->next;
		i = 0;
	}
	//printf("i = %d\n", i);
	//printf("tunnbr = %d\n", tunnbr);
	tunnbr = 0;
	filist = filistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				//printf("tunnbr = %d, roomlist->name = %s\n", tunnbr, roomlist->name);
				tunnbr++;
			}
			filist = filist->next;
		}
		printf("tunnbr = %d, roomlist->name = %s\n", tunnbr, roomlist->name);
		roomlist->tunnels = (char**)malloc(sizeof(char*) * tunnbr);
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;

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
	ft_place_start(filistart, roomlist);
	ft_place(filistart, roomlist);
	ft_show_roomlist(roomlist);




















	return (0);
}
