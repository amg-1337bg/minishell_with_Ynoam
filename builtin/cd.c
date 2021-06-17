/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:09:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/05 18:31:53 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

/*
**if (oldpwd && oldpwd->value == NULL)
**	mdf_env(env, "OLDPWD", ft_strdup(""));
**else if (oldpwd && oldpwd->value != NULL)
**	mdf_env(env, "OLDPWD", ft_strdup(hna));
*/
int	cd2(t_env *env, char *hna)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*pwdold;

	pwd = search_env_for_node(env, "PWD");
	if (pwd && pwd->value)
		pwdold = ft_strdup(pwd->value);
	else
		pwdold = ft_strdup("");
	if (pwd)
		mdf_env(env, "PWD", getcwd(NULL, 0));
	oldpwd = search_env_for_node(env, "OLDPWD");
	if (oldpwd)
		mdf_env(env, "OLDPWD", pwdold);
	ft_free(&hna);
	return (1);
}

int	cd(t_env *env, t_args *args)
{
	char	*hna;
	t_env	*home;

	hna = getcwd(NULL, 0);
	if (args)
	{
		if (!chdir(args->arg) && cd2(env, hna))
			return (0);
	}
	else
	{
		home = search_env_for_node(env, "HOME");
		if ((home == NULL || home->value == NULL) && ft_free(&hna))
		{
			put_error("HOME not set", "cd");
			return (1);
		}
		if (!chdir(home->value) && cd2(env, hna))
			return (0);
	}
	ft_free(&hna);
	hna = ft_strjoin("cd: ", args->arg);
	put_error(strerror(errno), hna);
	ft_free(&hna);
	return (1);
}
