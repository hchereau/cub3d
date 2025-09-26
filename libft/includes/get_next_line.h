/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:17:41 by imback            #+#    #+#             */
/*   Updated: 2024/09/07 11:48:58 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <aio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

enum				e_line_status
{
	error_line = -1,
	complete_line,
	uncomplete_line
};

typedef uint8_t	t_byte;

char				*get_next_line(int fd);
char				*ft_strnjoin(char *s1, char const *s2, const size_t size);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
enum e_line_status	read_line_until_new_line(char **line, char *buffer, int fd);

#endif
