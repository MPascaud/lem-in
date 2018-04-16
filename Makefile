# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 20:57:47 by mpascaud          #+#    #+#              #
#    Updated: 2018/04/16 16:55:32 by mpascaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a

TAGS = 

SRC = lem-in.c get_next_line.c ft_strnew.c ft_strlen.c ft_strncat.c ft_strcpy.c ft_isdigit.c

BIN = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@ gcc $(TAGS) -c $(SRC)
	@ ar rc $(NAME) $(BIN)
	@ ranlib $(NAME)
	@ gcc -fsanitize=address -o lem-in lem-in.c lem-in.a

clean:
	@ rm -rf $(BIN)

fclean: clean
	@ rm -rf $(NAME)
	@ rm -rf lem-in

re: fclean all


.PHONY: all clean fclean re