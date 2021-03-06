/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:38:21 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/05 14:50:25 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_PARSING_H
# define DATATYPES_PARSING_H

typedef struct s_operator{
    char *type; // ">" or ">>" or "<"
    char *file;
    struct s_operator *next;
}              t_files;

typedef struct s_args
{
    char *arg;
    struct s_args *next;
}               t_args;


typedef struct s_command
{
    char    *cmd;
    t_args  *args;
    t_files *files;
    char    *full;
    int     pipe;
    struct s_command *next;
}           t_cmd;

typedef struct s_environment
{
    char *key;
    char *value;
    struct s_environment *next;
}               t_env;

t_env   *g_env;
t_cmd   *g_cmd;

#endif