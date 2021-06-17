# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/06/12 15:17:17 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = executing/execute.c \
	  executing/execute1.c \
	  executing/execute2.c \
	  executing/execute3.c \
	  executing/execute4.c \
	  parsing/checkers.c \
	  parsing/clean_rep_utils.c \
	  parsing/clean_replace.c \
	  parsing/dollar_func.c \
	  parsing/dollar_func1.c \
	  parsing/env.c \
	  parsing/errors.c \
	  parsing/free_struct.c \
	  parsing/get_cmd.c \
	  parsing/history.c \
	  parsing/linked_list.c \
	  parsing/main.c \
	  parsing/modify_env.c \
	  parsing/parse_cmd.c \
	  parsing/pipe.c \
	  parsing/quotes.c \
	  parsing/quotes1.c \
	  parsing/redirection.c \
	  parsing/signals.c \
	  parsing/terminal.c \
	  parsing/terminal1.c \
	  builtin/cd.c \
	  builtin/echo.c \
	  builtin/env.c \
	  builtin/exit.c \
	  builtin/export.c \
	  builtin/export2.c \
	  builtin/pwd.c \
	  builtin/unset.c \
	  
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

$(NAME): $(SRC)
	@make -C ./libft
	@gcc -g $(FLAGS) $(SRC) libft/libft.a -ltermcap
	@ mv a.out $(NAME)

clean:
	@make clean -C ./libft
	@rm -rf ./*.o

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all
