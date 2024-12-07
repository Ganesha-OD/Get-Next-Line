/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:30:14 by go-donne          #+#    #+#             */
/*   Updated: 2024/12/07 10:35:06 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Combines existing buffer with new data
 *
 * @param existing Current buffer content (will be freed)
 * @param new_data New data to append (not freed)
 * @return char* New allocated buffer with combined data, or NULL on error
 *
 * @details
 * - Allocates new memory for combined string
 * - Copies existing content (if any) and new data
 * - Frees existing buffer regardless of success
 * - Ensures null-termination of result
 *
 * @note Memory ownership: Takes ownership of existing,
 * 		new_data remains unchanged
 */
char	*join_buffers(char *existing, char *new_data)
{
	char	*combined;
	char	*ptr;
	char	*start;

	if (!new_data)
		return (existing);
	combined = malloc(sizeof(char)
			* ((buffer_line_len(existing) + buffer_line_len(new_data)) + 1));
	if (!combined)
		return (free(existing), NULL);
	ptr = combined;
	start = existing;
	while (existing && *existing)
		*ptr++ = *existing++;
	while (new_data && *new_data)
		*ptr++ = *new_data++;
	*ptr = '\0';
	free (start);
	return (combined);
}

/**
 * @brief Processes the result of a read operation
 *
 * @param buffer Current buffer content
 * @param temp_buf Temporary buffer containing new read data
 * @param bytes_read Number of bytes from last read
 * @return char* Updated buffer or NULL on error/EOF
 *
 * @details
 * - Handles read results: EOF, errors, and successful reads
 * - Null-terminates temp_buf at bytes_read
 * - Combines buffers on successful read
 *
 * @note Does not free temp_buf - caller maintains ownership
 */
char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read)
{
	if (bytes_read < 0)
		return (free(buffer), NULL);
	if (bytes_read == 0)
	{
		if (!buffer || !buffer[0])
			return (NULL);
		return (buffer);
	}
	temp_buf[bytes_read] = '\0';
	return (join_buffers(buffer, temp_buf));
}

/**
 * @brief Reads from file descriptor into buffer until newline or EOF
 *
 * @param fd File descriptor to read from
 * @param buffer Current buffer content
 * @return char* Updated buffer with new data, or NULL on error/EOF
 *
 * @details
 * - Allocates temporary buffer for reading
 * - Performs repeated reads until newline or EOF
 * - Manages memory for temporary buffer
 * - Combines read data with existing buffer
 *
 * @note Takes ownership of input buffer, returns new or NULL
 */
char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buf;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	temp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (free(buffer), NULL);
	while (!find_newline(buffer))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		buffer = process_read(buffer, temp_buf, bytes_read);
		if (!buffer || bytes_read <= 0)
			break ;
	}
	free(temp_buf);
	return (buffer);
}

/**
 * @brief Reads a line from a file descriptor
 *
 * @param fd File descriptor to read from
 * @return char* Newly allocated string containing the line, or NULL on error/EOF
 *
 * @details
 * - Returns a line ending in newline unless it's the last line without one
 * - Manages a static buffer between calls to maintain state
 * - Handles memory allocation for returned line
 * - Supports multiple file descriptors through static buffer management
 *
 * @note
 * - Caller is responsible for freeing the returned string
 * - Returns NULL on EOF, error, or invalid parameters
 * - Thread-unsafe due to static buffer
 */
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
