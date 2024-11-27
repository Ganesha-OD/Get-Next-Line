/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:30:14 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 17:13:30 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *join_buffers(char *existing, char *new_data)
{
	char	*combined;
	size_t 	total_len;
	size_t 	i;
	size_t 	j;

	total_len = buffer_line_len(existing) + buffer_line_len(new_data);
    combined = malloc(sizeof(char) * (total_len + 1));
	if (!combined)
		return (handle_error(existing, NULL));
	i = 0;
	if (existing)
	{
		while (existing[i])
		{
			combined[i] = existing[i];
			i++;
		}
	}
	j = 0;
	while (new_data[j])
		combined[i++] = new_data[j++];
	combined[i] = '\0';
	return (combined);
}

char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read)
{
	char	*joined_buf;
	if (bytes_read < 0)
		return (handle_error(buffer, temp_buf));
	if (bytes_read == 0)
	{
		if (!buffer || !buffer[0])
			return (handle_error(buffer, temp_buffer));
		return (buffer);
	}
	temp_buf[bytes_read] = '\0';
	joined_buf = join_buffers(buffer, temp_buf);
	if (!joined_buf)
		return (handle_error(buffer, temp_buf));
	free(buffer);
	return (joined_buf);
}

char *read_to_buffer(int fd, char *buffer)
{
	char	*temp_buf;
	ssize_t	bytes_read;

	temp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (handle_error(buffer, NULL));
	while (1)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		buffer = process_read(buffer, temp_buf, bytes_read);
		if (!buffer || (!find_newline(buffer) && bytes_read == 0))
			break;
		if (find_newline(buffer))
			break;
	}
	free(temp_buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (buffer)
			return (handle_error(buffer, NULL));
		return (NULL);
	}
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
