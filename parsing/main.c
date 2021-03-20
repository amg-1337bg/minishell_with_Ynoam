/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/16 16:10:50 by bamghoug         ###   ########.fr       */
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
    tmp = s_env;
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

void    getenvp(t_env **s_env, char **envp)
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
                if ((tmp = ft_lstlst(*s_env)) != NULL)
                    tmp->next = fill;
                else
                    *s_env = fill;
                break ;
            }
        }
    }
}

void    signal_detected(int sig)
{
    write(1, "\n", 2);
    write(1, Minishell, ft_strlen(Minishell));
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env *s_env;
    t_cmd *s_cmd;
    t_cmd *test;
    int cmd_return;
    int     sign = 0;
    
    s_env = NULL;
    s_cmd = NULL;
    cmd_return = 0;
    getenvp(&s_env, envp);
    while(1)
    {
        write(1, Minishell, ft_strlen(Minishell));
        get_next_line(0, &line);
        get_cmd(&s_cmd, &s_env, line);
        // test = s_cmd;
        // // had lwhile kat afficher dakchi li kaine struct cmd
        // while (test)
        // {
        //     printf("cmd = %s\n", test->cmd);
        //     // had lwhile kat afficher l arguments
        //     printf("/*****arguments*****/\n");
        //     while (test->args)
        //     {
        //         printf("%20s\n", test->args->arg);
        //         test->args = test->args->next;
        //     }

        //     //had lwhile kat afficher lredirection
        //     printf("/******redirection*****/\n");
        //     while (test->files)
        //     {
        //         printf("%20%type %s file = %s\n", test->files->type, test->files->file);
        //         test->files = test->files->next;
        //     }

        //     printf("/******PIPE*****/\n");
        //     while (test->pipe)
        //     {
        //         printf("pipe cmd = %s\n",test->pipe->cmd);
        //         while (test->pipe->args)
        //         {
        //             printf("%20s\n", test->pipe->args->arg);
        //             test->pipe->args = test->pipe->args->next;
        //         }
                
        //         test->pipe = test->pipe->next;
        //     }
        //     // printf("full = %s\n", test->full);
        //     test = test->next;
        // }
        // use create_envp to create char** enviroment
        cmd_return = execute(s_cmd, NULL);
        free_cmd(&s_cmd);
    }
}