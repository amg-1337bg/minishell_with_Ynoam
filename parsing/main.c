/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/31 12:17:36 by bamghoug         ###   ########.fr       */
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
    write(1,"\b\b  \b\b", 6);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env *s_env;
    t_cmd *s_cmd;
    t_cmd *test;
    t_args *test_arg;
    t_files *test_file;
    t_cmd   *test_pipe;
    int cmd_return;
    int     sign = 0;
    
    s_env = NULL;
    s_cmd = NULL;
    cmd_return = 0;
    getenvp(&s_env, envp);
    signal(SIGQUIT, signal_detected);
    while(1)
    {
        write(1, Minishell, ft_strlen(Minishell));
        get_next_line(0, &line);
        get_cmd(&s_cmd, &s_env, line);
        // {
            test = s_cmd;
            // had lwhile kat afficher dakchi li kaine struct cmd
            while (test)
            { 
                printf("cmd = %s\n", test->cmd);
                // had lwhile kat afficher l arguments
                printf("/*****arguments*****/\n");
                test_arg = test->args;
                while (test_arg)
                {
                    printf("%20s\n", test_arg->arg);
                    test_arg= test_arg->next;
                }

                //had lwhile kat afficher lredirection
                printf("/******redirection*****/\n");
                test_file = test->files;
                while (test_file)
                {
                    printf("%20%type %s file = %s\n", test_file->type, test_file->file);
                    test_file = test_file->next;
                }

                printf("/******PIPE*****/\n");
                test_pipe = test->pipe;
                while (test_pipe)
                {
                    printf("pipe cmd = %s\n",test_pipe->cmd);
                    test_arg = test_pipe->args;
                    while (test_arg)
                    {
                        printf("%20s\n", test_arg->arg);
                        test_arg = test_arg->next;
                    }
                    test_pipe = test_pipe->next;
                }
                // printf("full = %s\n", test->full);
                test = test->next;
            }
            // use create_envp to create char** enviroment
            // cmd_return = execute(s_cmd, NULL)
        printf("***************************Execution*************************\n");
        cmd_return = execute(s_cmd, create_envp(s_env));
        // }
        // else
        //     printf("ERROR\n");
        free_cmd(&s_cmd);
    }
}
