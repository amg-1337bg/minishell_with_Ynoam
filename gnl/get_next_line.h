/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:58:37 by bamghoug          #+#    #+#             */
/*   Updated: 2021/02/23 09:57:17 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

int		check(char *string);
char	*before_n(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*after_n(char *s);
size_t	ft_strlen(const char *s);
int		get_next_line(int fd, char **line);
int		work_todo(int fd, char *buf, char **line);
int		rest_check(char *res, char **line);

#endif
