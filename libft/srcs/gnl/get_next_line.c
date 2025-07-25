/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/06/07 18:41:59 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	replace_rest(char *rest,
			enum e_line_status line_status)
{
	const char	*end_line = ft_strchr(rest, '\n');
	size_t		i;

	if (line_status == complete_line)
	{
		ft_strlcpy(rest, end_line + 1,
			ft_strlen(end_line) + 1);
	}
	else
	{
		i = 0;
		while (i < BUFFER_SIZE + 1)
		{
			((t_byte *)rest)[i] = (t_byte) '\0';
			++i;
		}
	}
}

static enum e_line_status	fill_line_from_src(char **line, char *src)
{
	enum e_line_status	line_status;
	const char			*new_line = ft_strchr(src, '\n');
	char *const			temp_line = *line;
	const size_t		len_line = new_line - src +1;

	if (new_line != NULL)
	{
		*line = ft_strnjoin(*line, src, len_line);
		free(temp_line);
		line_status = complete_line;
	}
	else
	{
		*line = ft_strnjoin(*line, src, ft_strlen(src) + 1);
		free(temp_line);
		line_status = uncomplete_line;
	}
	if (*line == NULL)
	{
		return (error_line);
	}
	return (line_status);
}

static enum e_line_status	read_line_from_file(char **line, char *const rest,
	const int fd)
{
	char				buffer[BUFFER_SIZE + 1];
	enum e_line_status	line_status;
	char				*end_line;

	line_status = read_line_until_new_line(line, buffer, fd);
	if (line_status == uncomplete_line)
	{
		end_line = ft_strchr(buffer, '\n');
		line_status = fill_line_from_src(line, buffer);
		if (line_status == complete_line)
		{
			ft_strlcpy(rest, end_line + 1,
				(buffer + ft_strlen(buffer)) - end_line);
		}
	}
	return (line_status);
}

static enum e_line_status	read_line_from_rest(char **line, char *const rest)
{
	enum e_line_status	line_status;

	line_status = uncomplete_line;
	if (ft_strlen(rest) > 0)
	{
		line_status = fill_line_from_src(line, rest);
		replace_rest(rest, line_status);
	}
	return (line_status);
}

char	*get_next_line(int fd)
{
	char				*line;
	static char			rest[FOPEN_MAX][BUFFER_SIZE + 1] = {""};
	enum e_line_status	line_status;

	line = NULL;
	if (fd >= 0 && fd < FOPEN_MAX)
	{
		line_status = read_line_from_rest(&line, rest[fd]);
		if (line_status == uncomplete_line)
		{
			line_status = read_line_from_file(&line, rest[fd], fd);
		}
	}
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test3.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }
