/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:56:50 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 21:48:52 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(void)
{
	write (1, "ERROR\n", ft_strlen("ERROR\n"));
}

void	printed_errors(int error_code)
{
	if (error_code == -258)
		printf("syntax error near unexpected token\n");
	else if (error_code == -3)
		printf("ERROR: No Multiline Commands\n");
}

int	put_error(char *errorstr, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errorstr, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
