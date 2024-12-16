/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:21:36 by rrochd            #+#    #+#             */
/*   Updated: 2024/10/24 00:17:57 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stored)
{
	char	*line;
	char	*temp;
	size_t	len;

	if (*stored == NULL)
		return (NULL);
	len = 0;
	while ((*stored)[len] && (*stored)[len] != '\n')
		len++;
	if ((*stored)[len] == '\n')
		len++;
	line = ft_substr(*stored, 0, len);
	if ((*stored)[len] == '\0')
	{
		free(*stored);
		*stored = NULL;
	}
	else
	{
		temp = ft_strdup(*stored + len);
		free(*stored);
		*stored = temp;
	}
	return (line);
}

static int	read_to_buffer(int fd, char **stored)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	if (*stored)
	{
		tmp = ft_strjoin(*stored, buffer);
		free(*stored);
		*stored = tmp;
	}
	else
		*stored = ft_strdup(buffer);
	free(buffer);
	return (bytes_read);
}

static void	*free_stored(char **stored)
{
	free(*stored);
	*stored = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stored[FOPEN_MAX];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	while (stored[fd] == NULL || !ft_strchr(stored[fd], '\n'))
	{
		bytes_read = read_to_buffer(fd, &stored[fd]);
		if (bytes_read < 0)
			return (free_stored(&stored[fd]));
		if (bytes_read == 0)
			break ;
	}
	line = extract_line(&stored[fd]);
	if (!line || *line == '\0')
	{
		free(line);
		return (free_stored(&stored[fd]));
	}
	return (line);
}

