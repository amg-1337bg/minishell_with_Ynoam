/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/02 15:55:15 by bamghoug         ###   ########.fr       */
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

char **create_envp(t_env *s_env, char *cmd)
{
    char **ret;
    t_env *tmp;
    int i;
    int j;

    i = 0;
    tmp = s_env->next;
    while (tmp != NULL && ++i)
        tmp = tmp->next;
    j = 0;
    tmp = s_env->next;
    if ((ret = (char**)malloc((i + 1) * sizeof(char*))) == NULL)
        write(1, strerror(errno), ft_strlen(strerror(errno)));
    while (tmp != NULL)
    {
        ret[j] = ft_strjoin(tmp->key, "=");
        if (tmp->key && ft_strncmp(tmp->key, "_", ft_strlen("_")) == 0 && ft_strlen(tmp->key) == ft_strlen("_"))
            ret[j] = ft_strjoin(ret[j], cmd); //LEAKS HERE
        else
            ret[j] = ft_strjoin(ret[j], tmp->value); //LEAKS HERE
        j++;
        tmp = tmp->next;
    }
    ret[j] = NULL;
    return (ret);
}

void    changenvp(t_env *env)
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
				break;
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
			mdf_env(env, "SHLVL", ft_itoa(ft_atoi(search_env(env, "SHLVL")) + 1));
	}
	else
		crt_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
}

void    getenvp(t_env **s_env, char **envp)
{
    int j;
    int i;
    t_env *tmp;
    t_env *fill;

    i = -1;
    fill = malloc(sizeof(t_env));
    fill->key = NULL;
    fill->value = NULL;
    fill->next = NULL;
    *s_env = fill;
    while (envp[++i] != NULL)
    {
        j = -1;
        if ((fill = (t_env *)malloc(sizeof(t_env))) == NULL)
            write(1, strerror(errno), ft_strlen(strerror(errno)));
        while (envp[i][++j] != '\0')
            if (envp[i][j] == '=')
            {
                fill->key = ft_substr(envp[i], 0, j);
                fill->value = ft_strdup(&envp[i][j + 1]);
                fill->next = NULL;
                if ((tmp = ft_lstlst(*s_env)) != NULL)
                    tmp->next = fill;
                break;
            }
    }
}

void    ctrl_c(int c)
{
    char *cap;
    
    write(1, "\n", 1);
    write(1, Minishell, ft_strlen(Minishell));
    cap = tgetstr("sc", 0);
    write(1, cap, ft_strlen(cap));
    g_signal = 1;
}


int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env *s_env;
    t_cmd *s_cmd;
    int cmd_return;
    t_line  *h_line[3];
    struct termios old;
    
    s_env = NULL;
    s_cmd = NULL;
    cmd_return = 0;
    getenvp(&s_env, envp);
    changenvp(s_env);
    tcgetattr(STDIN_FILENO, &old);
    tgetent(0, getenv("TERM"));
    h_line[0] = NULL;
    h_line[1] = NULL;
    h_line[2] = NULL;
    while(1)
    {
        line = get_line(h_line, old, &cmd_return);
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        if (get_cmd(&s_cmd, s_env, line, &cmd_return) == 0)
            cmd_return = execute(s_cmd, s_env, cmd_return);
        free_cmd(&s_cmd);
        free(line);
    }
    return (0);
}
