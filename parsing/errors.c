/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:56:50 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/11 18:18:40 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error()
{
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
}


// Ynoam
void	put_error(char *errorstr,char *filename)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(filename,2);
	ft_putstr_fd(": ",2);
	ft_putstr_fd(errorstr,2);
	ft_putstr_fd("\n",2);
}