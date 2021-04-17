/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:09:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/17 17:45:52 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	cd2(t_env *env, char *hna)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = search_env_for_node(env, "PWD");
	if (pwd)
		mdf_env(env, "PWD", getcwd(NULL, 0));
	oldpwd = search_env_for_node(env, "OLDPWD");
	if (oldpwd && oldpwd->value == NULL)
		mdf_env(env, "OLDPWD", ft_strdup(""));
	else if (oldpwd && oldpwd->value != NULL)
		mdf_env(env, "OLDPWD", hna);
	else
		free(hna);
	return (1);
}

int	cd(t_env *env, t_args *args)
{
	char	*hna;
	t_env	*pwd;

	hna = getcwd(NULL, 0);
	if (args)
	{
		if (!chdir(args->arg) && cd2(env, hna))
			return (0);
		else
		{
			ft_free(&hna);
			return (put_error(strerror(errno), args->arg));
		}
	}
	else
	{
		pwd = search_env_for_node(env, "HOME");
		if (pwd == NULL || pwd->value == NULL)
		{
			ft_free(&hna);
			put_error("HOME not set", "cd");
			return (1);
		}
		else if (!chdir(pwd->value))
		{
			ft_free(&hna);
			cd2(env, hna);
			return (0);
		}
	}
	ft_free(&hna);
	hna = ft_strjoin("cd: ", args->arg);
	put_error(strerror(errno), hna);
	ft_free(&hna);
	return (1);
}
