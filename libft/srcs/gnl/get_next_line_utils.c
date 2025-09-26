/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:15:12 by imback            #+#    #+#             */
/*   Updated: 2024/06/08 15:29:09 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char *s1, char const *s2, const size_t size)
{
	char	*join;
	size_t	size1;
	size_t	size2;

	size1 = 0;
	size2 = 0;
	if (s1 != NULL)
		size1 = ft_strlen(s1);
	if (s2 != NULL)
		size2 = ft_strlen(s2);
	if (size2 > size)
		size2 = size;
	join = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size2 + 1);
	}
	return (join);
}

enum e_line_status	read_line_until_new_line(char **line, char *buffer,
	const int fd)
{
	const int	bytes_read = read(fd, buffer, BUFFER_SIZE);
	char		*new_line;
	char *const	temp_line = *line;

	if (bytes_read < 0)
	{
		free(*line);
		*line = NULL;
		return (error_line);
	}
	buffer[bytes_read] = '\0';
	new_line = ft_strchr(buffer, '\n');
	if (bytes_read > 0 && new_line == NULL)
	{
		*line = ft_strnjoin(*line, buffer, bytes_read);
		free(temp_line);
		if (*line == NULL)
			return (error_line);
		return (read_line_until_new_line(line, buffer, fd));
	}
	if (new_line == NULL && bytes_read == 0)
		return (complete_line);
	return (uncomplete_line);
}
