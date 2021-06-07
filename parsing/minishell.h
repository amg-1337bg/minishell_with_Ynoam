/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:29:58 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 15:32:03 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"
# define MINISHELL "\033[38;5;6mprompt >\e[m "
# define CMD_NOT_FOUND "command not found"
# define NO_SUCH_FILE_OR_DIR "No such file or directory"
# define SYNTAX_EROOR -258
# define NO_MULTI -3
# include "parsing.h"
# include "../executing/execute.h"
# include "../builtin/builtin.h"

#endif