/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:19:18 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/31 19:20:31 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int     ft_exit(char **args)
{
    long long int j;
    int i;


    if (args[1])
    {
        j = 0;
        while (args[1][j])
        {
            if (!ft_isdigit(args[1][j]))
            {
                put_error("numeric argument required", ft_strjoin("exit: ", args[1]));
                exit(255);
            }
            j++;
        }
        if (j >= 20)
        {
            put_error("numeric argument required", ft_strjoin("exit: ", args[1]));
            exit(255);
        }
        if (args[2])
        {
            put_error("too many arguments", "exit");
            return (1);
        }
        j = 0;
        i = 0;
        ft_putstr_fd("exit\n", 2);
        while (args[1][i] >= 48 && args[1][i] <= 57)
            j = (j * 10) + args[1][i++] - 48;
        exit(j);
    }
    ft_putstr_fd("exit\n", 2);
    exit(0);
    return (0);
}