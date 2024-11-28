/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:30:14 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/28 10:53:01 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_buffers(char *existing, char *new_data)
{
	char	*combined;
	char	*ptr;

	combined = malloc(sizeof(char)
			* ((buffer_line_len(existing) + buffer_line_len(new_data)) + 1));
	if (!combined)
		return (free(existing), NULL);
	ptr = combined;
	while (existing && *existing)
		*ptr++ = *existing++;
	while (*new_data)
		*ptr++ = *new_data++;
	*ptr = '\0';
	free (existing);
	return (combined);
}

char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read)
{
	if (bytes_read <= 0)
	{
		if (bytes_read < 0 || !buffer || !buffer[0])
			return (NULL);
		return (buffer);
	}
	temp_buf[bytes_read] = '\0';
	return (join_buffers(buffer, temp_buf));
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buf;
	ssize_t	bytes_read;

	temp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (free(buffer), NULL);
	while (1)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		buffer = process_read(buffer, temp_buf, bytes_read);
		if (!buffer || (!find_newline(buffer) && bytes_read == 0))
			break ;
		if (find_newline(buffer))
			break ;
	}
	free(temp_buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (free (buffer), buffer = NULL, NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
		return (free (buffer), buffer = NULL, NULL);
	buffer = update_buffer(buffer);
	return (line);
}
