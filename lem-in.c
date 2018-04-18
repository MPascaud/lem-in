/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/04/18 21:50:58 by mpascaud         ###   ########.fr       */
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
	int		i;

	i = 0;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		printf("roomlist->name = %s\n", roomlist->name);
		printf("roomlist->place = %d\n", roomlist->place);
		while ((roomlist->beftunnels)[i] != NULL)
		{
			printf("roomlist->beftunnels[%d] = %s\n", i, roomlist->beftunnels[i]);
			i++;
		}
		i = 0;
		while ((roomlist->tunnels)[i] != NULL)
		{
			printf("roomlist->tunnels[%d] = %s\n", i, roomlist->tunnels[i]);
			i++;
		}
		printf("\n");
		i = 0;
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

void	ft_place_end(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##end"))
		{
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = -2;
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
		if ((filist->line)[i] != (roomlist->name)[i] || (filist->line)[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int		ft_disiz_beftunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;
	int		j;

	there_is_tunnel = 0;
	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
		{
			there_is_tunnel = 1;
			i++;
			break ;
		}
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);
//	printf("coucou i = %d\n", i);
//	i = 0;

	while ((roomlist->name)[j] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[j] || (filist->line)[i] == '\0')
			return (0);
		i++;
		j++;
	}
//	printf("filist->line = %s, roomlist->name = %s\n", filist->line, roomlist->name);

	return (1);
}

char	*ft_link(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;
	int		start;
	int		tmp;

	i = 0;
	start = 0;
	tmp = 0;
	while ((filist->line)[start] != '-')
		start++;
	start++;
	tmp = start;
	while ((filist->line)[tmp] != '\0')
	{
		tmp++;
		i++;
	}
	//printf("i = %d\n", i);
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	tmp = start;
	i = 0;
	while ((filist->line)[tmp] != '\0')
	{
		tunname[i] = (filist->line)[tmp];
		i++;
		tmp++;
	}
	tunname[i] = '\0';
	return (tunname);
}

char	*ft_beflink(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;
	//int		tmp;

	i = 0;
	//tmp = 0;
	while ((filist->line)[i] != '-')
	{
		i++;
	}
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	//tmp = i;
	i = 0;
	while ((filist->line)[i] != '-')
	{
		tunname[i] = (filist->line)[i];
		i++;
	}
	tunname[i] = '\0';
	return (tunname);
}


void	ft_tunnels(t_filist *filist, t_roomlist *roomlist)
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
		//printf("tunnbr = %d, roomlist->name = %s\n", tunnbr, roomlist->name);
		roomlist->tunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				(roomlist->tunnels)[i] = ft_link(filist, roomlist);
				i++;

			}
			filist = filist->next;
		}
		(roomlist->tunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}
	//(roomlist->tunnels)[i] = ft_link(filist, roomlist);


	tunnbr = 0;
	filist = filistart;
	roomlist = roomlistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				tunnbr++;
			}
			filist = filist->next;
		}
		roomlist->beftunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	filist = filistart;
	tunnbr = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				(roomlist->beftunnels)[i] = ft_beflink(filist, roomlist);
				i++;
			}
			filist = filist->next;
		}
		(roomlist->beftunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}
}

//place, max

//calcul des places
//si le next = end ou -2: 
//malloc char** place + 1(end) + 1(NULL), !!une seule fois
//max = place - 1,
//place devient -2,
//name sur way
//si la place d'un predecesseur = max(et pas -1 ou -2), on y va
//
//refaisage


//defilement roomlist
//pour chacun : defilement des precedents; si precedent->place != -1 et -2, place = precedent->place + 1


void	ft_check_previous_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	int		empty;

	empty = 0;
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
		{
			//printf("roomlistart->name = %s, (roomlist->beftunnels)[i] = %s, i = %d \n", roomlistart->name, (roomlist->beftunnels)[i], i);
			if (roomlistart->place == -1 && roomlist->place != -2)
			{
				roomlistart->place = roomlist->place + 1;
				return ;
			}
		}
		roomlistart = roomlistart->next;
	}
	//return 1 si place = -1
}

void	ft_check_next_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
		{
			if ((roomlistart->place == -1 || (roomlistart->place > roomlist->place + 1)) && roomlist->place != -2)
			{
				roomlistart->place = roomlist->place + 1;
				return ;
			}
		}
		roomlistart = roomlistart->next;
	}
}


void	ft_place(t_filist *filist, t_roomlist* roomlist)
{
	int			i;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	filistart = filist;
	roomlistart = roomlist;
	filist = filist->next;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			ft_check_previous_place(roomlist, i, roomlistart);
			//if (ft_check_previous_place(roomlist, i, roomlistart) == 1)
			//{
			//	ft_change_previous_place(roomlist);
				//roomlist = roomlistart;
			//	break ;
			//}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	i = 0;
	while (roomlist != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			ft_check_next_place(roomlist, i, roomlistart);
			i++;
		}
		i = 0;
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
	ft_place_start(filistart, roomlist);
	ft_place_end(filistart, roomlist);
	ft_tunnels(filistart, roomlist);

	ft_place(filistart, roomlist);

	ft_show_roomlist(roomlist);



















	return (0);
}
