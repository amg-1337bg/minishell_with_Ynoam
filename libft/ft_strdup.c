/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:49:24 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/16 15:26:13 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*ptrcp;
	int		x;

	x = ft_strlen(string) + 1;
	ptrcp = (char *)malloc(x);
	if (!ptrcp)
		return (NULL);
	while (x-- > 0)
		ptrcp[x] = (char)string[x];
	return (ptrcp);
}
