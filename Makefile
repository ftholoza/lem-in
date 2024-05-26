# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francesco <francesco@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 07:04:09 by francesco         #+#    #+#              #
#    Updated: 2024/05/22 18:11:49 by francesco        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror  -g3
HEADER = lem_in.h
SRCS = get_next_line.c ft_lstdel_last.c init_data.c read_file.c ft_strncmp.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c get_paths.c ft_lstlast.c ft_lstnew.c ft_lstsize.c
MAIN = main.c
OBJ = $(SRCS:.c=.o)
NAME = a.out
REALNAME = lem_in


all : $(REALNAME)
re : fclean all
$(REALNAME) : $(NAME)
	mv $(NAME) $(REALNAME)
$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(MAIN) $(OBJ)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(REALNAME)