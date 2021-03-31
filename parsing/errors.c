/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:56:50 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/29 10:14:29 by bamghoug         ###   ########.fr       */
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
void	put_error(char *errorstr,char *filename, char *builtin)
{
	if (builtin != NULL)
	{
		ft_putstr_fd(builtin, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(filename,2);
	ft_putstr_fd(": ",2);
	ft_putstr_fd(errorstr,2);
	ft_putstr_fd("\n",2);
}