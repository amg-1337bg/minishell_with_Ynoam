/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/02/24 12:31:24 by bamghoug         ###   ########.fr       */
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

char **create_envp(t_env *tmp)
{
    char **ret;
    int i;
    int j;

    i = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    j = 0;
    tmp = g_env;
    if ((ret = (char**)malloc((i + 1) * sizeof(char*))) == NULL)
        write(1, strerror(errno), ft_strlen(strerror(errno)));
    while (tmp != NULL)
    {
        ret[j] = ft_strjoin(tmp->key, "=");
        ret[j] = ft_strjoin(ret[j], tmp->value);
        j++;
        tmp = tmp->next;
    }
    ret[j] = NULL;
    return (ret);
}

void    getenvp(char **envp)
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
                if ((tmp = ft_lstlst(g_env)) != NULL)
                    tmp->next = fill;
                else
                    g_env = fill;
                break ;
            }
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    argc = 0;
    argv = NULL;
    
    getenvp(envp);
    while(1)
    {
        write(1, Minishell, ft_strlen(Minishell));
        get_next_line(0, &line);
        
    }
}