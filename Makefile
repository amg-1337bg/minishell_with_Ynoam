# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/03/05 10:22:53 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c ./utils/errors.c ./utils/modify_env.c ./utils/get_cmd.c utils/parse_cmd.c \
		libft/libft.a
FLAGS = -Wall -Wextra 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	make clean -C ./libft
	rm -rf ./*.o

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all