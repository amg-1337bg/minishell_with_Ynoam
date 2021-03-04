/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/04 21:35:53 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*ft_lstlst(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_lstcmd(t_cmd *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

char **create_envp(t_env *s_env)
{
    char **ret;
    t_env *tmp;
    int i;
    int j;

    i = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    j = 0;
    tmp = s_env;
    if ((ret = (char**)malloc((i + 1) * sizeof(char*))) == NULL)
        write(1, strerror(errno), ft_strlen(strerror(errno)));
    while (tmp != NULL)
    {
        ret[j] = ft_strjoin(tmp->key, "=");
        ret[j] = ft_strjoin(ret[j], tmp->value); //LEAKS HERE
        j++;
        tmp = tmp->next;
    }
    ret[j] = NULL;
    return (ret);
}

void    getenvp(t_env *s_env, char **envp)
{
    int j;
    int i;
    t_env *tmp;
    t_env *fill;

    i = -1;
    while(envp[++i] != NULL)
    {
        j = -1;
        if ((fill = (t_env*)malloc(sizeof(t_env))) == NULL)
            write(1, strerror(errno), ft_strlen(strerror(errno)));
        while(envp[i][++j] != '\0')
        {
            if (envp[i][j] == '=')
            {
                fill->key = ft_substr(envp[i], 0, j);
                fill->value = ft_strdup(&envp[i][j + 1]);
                fill->next = NULL;
                if ((tmp = ft_lstlst(s_env)) != NULL)
                    tmp->next = fill;
                else
                    s_env = fill;
                break ;
            }
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env *s_env;
    t_cmd *s_cmd;
    
    s_env = NULL;
    s_cmd = NULL;
    //write(1, argv[argc], ft_strlen(argv[argc]));
    getenvp(s_env, envp);
    while(1)
    {
        write(1, Minishell, ft_strlen(Minishell));
        get_next_line(0, &line);
        get_cmd(&s_cmd, line);
        // use create_envp to create char** enviroment
    }
}