/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:38:21 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/07 15:53:19 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_PARSING_H
# define DATATYPES_PARSING_H

typedef struct s_operator
{
	char				*type;
	char				*file;
	int					dollar;
	struct s_operator	*next;
}	t_files;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;

typedef struct s_command
{
	char				*cmd;
	t_args				*args;
	t_files				*files;
	char				*full;
	struct s_command	*pipe;
	struct s_command	*next;
}	t_cmd;

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
	struct s_line	*prev;
}	t_line;

#endif