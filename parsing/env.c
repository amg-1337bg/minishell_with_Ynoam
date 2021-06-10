/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:13:07 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/05 14:02:10 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_envp(t_env *s_env, char *cmd)
{
	char	**ret;
	char	*char_tmp;
	t_env	*tmp;
	int		i;
	int		j;

	tmp = s_env->next;
	i = list_size(tmp);
	j = -1;
	ret = malloc((i + 1) * sizeof(char *));
	while (tmp != NULL)
	{
		ret[++j] = ft_strjoin(tmp->key, "=");
		char_tmp = ret[j];
		if (tmp->key && ft_strncmp(tmp->key, "_", ft_strlen("_")) == 0
			&& ft_strlen(tmp->key) == ft_strlen("_"))
			ret[j] = ft_strjoin(ret[j], cmd);
		else
			ret[j] = ft_strjoin(ret[j], tmp->value);
		free (char_tmp);
		tmp = tmp->next;
	}
	ret[++j] = NULL;
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
	if (shlvl[0] != 0)
	{
		while (shlvl[wow])
			if (!ft_isdigit(shlvl[wow++]))
				break ;
		if (shlvl[wow] != 0)
			return (crt_env(env, ft_strdup("SHLVL"), ft_strdup("1")));
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

t_env	*init_env(void)
{
	t_env	*fill;

	fill = malloc(sizeof(t_env));
	fill->key = NULL;
	fill->value = NULL;
	fill->next = NULL;
	return (fill);
}

void	getenvp(t_env **s_env, char **envp)
{
	int		j;
	int		i;
	t_env	*tmp;
	t_env	*fill;

	i = -1;
	*s_env = init_env();
	while (envp[++i] != NULL)
	{
		j = -1;
		fill = (t_env *)malloc(sizeof(t_env));
		while (envp[i][++j] != '\0')
		{	
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
}

int	list_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
