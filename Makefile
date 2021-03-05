# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/03/05 15:08:55 by ynoam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	executing/*.c  parsing/*.c   \
		libft/libft.a
FLAGS = -Wall -Wextra 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(SRC)

clean:
	make clean -C ./libft
	rm -rf ./*.o

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all