/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:13:12 by ynoam             #+#    #+#             */
/*   Updated: 2021/05/29 17:13:13 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../parsing/minishell.h"
# include <limits.h>

int		pwd(int *fd);
int		ft_exit(char **args);
int		ft_echo(char *argv[], int *fd);
int		ft_env(t_env *head, int *fd);
int		unset(t_env *head, char *argv[]);
int		ft_export(t_env *head, char *argv[], int *fd);
int		same(char *str1, char *str2);
void	print(t_env **head, int i, int *fd);
void	swap_env(t_env **arr, int k, int j);
void	sort_env(t_env **arr, int i, int *fd);
int		cd(t_env *env, t_args *args);
int		there_is_an_error(char *argv, int i);

#endif