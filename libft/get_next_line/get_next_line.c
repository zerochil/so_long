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

static char	*extract_line(t_string *stored, char *newline)
{
	char		*line;
	t_string	temp;

	if (stored->data == NULL || stored->size == 0)
		return (NULL);
	if (newline)
	{
		line = ft_substr(stored->data, 0, newline - stored->data + 1);
		string_init(&temp);
		string_append(&temp, newline + 1);
		string_destroy(stored);
		*stored = temp;
	}
	else
	{
		line = ft_strdup(stored->data);
		string_destroy(stored);
	}
	track_resource(line, free);
	return (line);
}

static int	read_buffer(int fd, t_string *stored)
{
	char	*buffer;
	int		bytes_read;

	buffer = track_malloc(BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		string_append(stored, buffer);
	}
	free_resource(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_string	stored[FOPEN_MAX];
	int				bytes_read;
	char			*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	if (!stored[fd].data)
		string_init(&stored[fd]);
	while (1)
	{
		newline = ft_strchr(stored[fd].data, '\n');
		if (newline)
			break;
		bytes_read = read_buffer(fd, &stored[fd]);
		if (bytes_read <= 0)
			break ;
	}
	return (extract_line(&stored[fd], newline));
}
