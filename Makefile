# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/03/04 18:02:17 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c ./utils/errors.c ./utils/modify_env.c ./utils/get_cmd.c \
		libft/libft.a
FLAGS = -Wall -Wextra 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean: 
	rm -rf ./*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all