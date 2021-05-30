# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/05/26 09:20:06 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	executing/*.c  parsing/*.c \
		builtin/*.c libft/libft.a 
FLAGS = -Wall -Wextra 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -g -fsanitize=address -ltermcap  $(FLAGS) $(SRC) -o $(NAME)

clean:
	make clean -C ./libft
	rm -rf ./*.o

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
