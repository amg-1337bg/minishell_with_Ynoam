# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/03/01 11:17:19 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
		./libft/libft.a \
		main.c ./utils/errors.c ./utils/modify_env.c ./utils/get_cmd.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean: 
	rm -rf ./*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all