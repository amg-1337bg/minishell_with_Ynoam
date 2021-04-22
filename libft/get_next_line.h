/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:12:02 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/22 14:31:43 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024

# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>

char	*ft_join(char *string1, char *string2);
int		ft_free(char **stk);
char	*ft_sub(char *string, size_t x);
char	*ft_from_newline(char *string, size_t x, size_t y, size_t z);
int		ft_search(char *source);
size_t	len(char *str);
int		get_next_line(int fd, char **line);

#endif
