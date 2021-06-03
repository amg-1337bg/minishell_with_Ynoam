/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:13:07 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 21:44:40 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_envp(t_env *s_env, char *cmd)
{
	char	**ret;
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = s_env->next;
	while (tmp != NULL && ++i)
		tmp = tmp->next;
	j = 0;
	tmp = s_env->next;
	ret = malloc((i + 1) * sizeof(char *));
	while (tmp != NULL)
	{
		ret[j] = ft_strjoin(tmp->key, "=");
		if (tmp->key && ft_strncmp(tmp->key, "_", ft_strlen("_")) == 0
			&& ft_strlen(tmp->key) == ft_strlen("_"))
			ret[j] = ft_strjoin(ret[j], cmd); //LEAKS HERE
		else
			ret[j] = ft_strjoin(ret[j], tmp->value); //LEAKS HERE
		j++;
		tmp = tmp->next;
	}
	ret[j] = NULL;
	return (ret);
}

void	changenvp(t_env *env)
{
	char	*shlvl;
	int		wow;

	mdf_env(env, "OLDPWD", NULL);
	mdf_env(env, "PWD", getcwd(NULL, 0));
	shlvl = search_env(env, "SHLVL");
	wow = 1;
	if (shlvl[0] != 0) // if is exist
	{
		while (shlvl[wow])
		{
			if (!ft_isdigit(shlvl[wow]))
				break ;
			wow++;
		}
		if (shlvl[wow] != 0)
		{
			crt_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
			return ;
		}
		if (ft_atoi(shlvl) > 998)
			mdf_env(env, "SHLVL", ft_strdup(""));
		else if (ft_atoi(shlvl) < 0)
			mdf_env(env, "SHLVL", ft_itoa(0));
		else
			mdf_env(env, "SHLVL",
				ft_itoa(ft_atoi(search_env(env, "SHLVL")) + 1));
	}
	else
		crt_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
}

void	getenvp(t_env **s_env, char **envp)
{
	int		j;
	int		i;
	t_env	*tmp;
	t_env	*fill;

	i = -1;
	fill = malloc(sizeof(t_env));
	fill->key = NULL;
	fill->value = NULL;
	fill->next = NULL;
	*s_env = fill;
	while (envp[++i] != NULL)
	{
		j = -1;
		fill = (t_env *)malloc(sizeof(t_env));
		while (envp[i][++j] != '\0')
			if (envp[i][j] == '=')
			{
				fill->key = ft_substr(envp[i], 0, j);
				fill->value = ft_strdup(&envp[i][j + 1]);
				fill->next = NULL;
				tmp = ft_lstlst(*s_env);
				if (tmp != NULL)
					tmp->next = fill;
				break ;
			}
	}
}
