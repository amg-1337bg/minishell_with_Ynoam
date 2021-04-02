<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:38:21 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/16 14:57:02 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_PARSING_H
# define DATATYPES_PARSING_H

// commands files

typedef struct s_operator{
    char *type; // ">" or ">>" or "<"
    char *file;
    struct s_operator *next;
}              t_files;

// commands args

typedef struct s_args
{
    char            *arg;
    struct s_args   *next;
}               t_args;

// commands

typedef struct s_command
{
    char    *cmd;
    t_args  *args;
    t_files *files;
    char    *full;
    struct s_command *pipe;
    struct s_command *next;
}           t_cmd;

// environment
typedef struct s_environment
{
    char *key;
    char *value;
    struct s_environment *next;
}               t_env;

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:38:21 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/28 11:02:39 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_PARSING_H
# define DATATYPES_PARSING_H

// commands files

typedef struct s_operator{
    char *type; // ">" or ">>" or "<"
    char *file;
    struct s_operator *next;
}              t_files;

// commands args

typedef struct s_args
{
    char            *arg;
    struct s_args   *next;
}               t_args;

// commands

typedef struct s_command
{
    char    *cmd;
    t_args  *args;
    t_files *files;
    char    *full;
    struct s_command *pipe;
    struct s_command *next;
}           t_cmd;

// environment
typedef struct s_environment
{
    char *key;
    char *value;
    struct s_environment *next;
}               t_env;

>>>>>>> 3bcf84087d2bc0269e1d5297f0b2371b8974bfa2
#endif