/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:56:50 by bamghoug          #+#    #+#             */
/*   Updated: 2021/04/17 15:33:00 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// BRAHIM
void    error()
{
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
}

void    printed_errors(int error_code, char *str)
{
    write(1, Minishell, ft_strlen(Minishell));
	if(error_code == -2)
		printf("syntax error near unexpected token '%s'\n", str);
	else if (error_code == -3)
		printf("ERROR: No Multiline Commands\n");
}

// Ynoam
int	put_error(char *errorstr,char *filename)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(filename,2);
	ft_putstr_fd(": ",2);
	ft_putstr_fd(errorstr,2);
	ft_putstr_fd("\n",2);
	return (1);
}
