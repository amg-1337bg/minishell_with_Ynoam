# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/04/09 18:53:41 by ynoam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	executing/*.c  parsing/*.c   \
		builtin/*.c libft/libft.a 
FLAGS = -Wall -Wextra 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -g -fsanitize=address -ltermcap $(FLAGS) $(SRC) -o $(NAME)

clean:
	make clean -C ./libft
	rm -rf ./*.o

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
