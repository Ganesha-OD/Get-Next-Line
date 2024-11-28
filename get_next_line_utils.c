/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/28 12:13:13 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Checks if buffer contains a newline character
 *
 * @param buffer String to search
 * @return int 1 if newline found, 0 if not
 *
 * @details
 * - Handles NULL buffer safely
 * - Scans until first newline or end of string
 * - No memory allocation/deallocation
 */
int	find_newline(char *buffer)
{
	char	*ptr;

	if (!buffer)
		return (0);
	ptr = buffer;
	while (*ptr)
	{
		if (*ptr == '\n')
			return (1);
		ptr++;
	}
	return (0);
}

/**
 * @brief Calculates length of string in buffer
 *
 * @param buffer String to measure
 * @return size_t Length of string
 *
 * @details
 * - Handles NULL buffer (returns 0)
 * - Counts until null terminator
 * - No memory allocation/deallocation
 */
size_t	buffer_line_len(char *buffer)
{
	char	*ptr;

	if (!buffer)
		return (0);
	ptr = buffer;
	while (*ptr)
		ptr++;
	return (ptr - buffer);
}

/**
 * @brief Extracts a line from buffer up to newline or EOF
 *
 * @param buffer Source buffer
 * @return char* New allocated string containing the line, or NULL on error
 *
 * @details
 * - Allocates memory for new line
 * - Includes newline character if present
 * - Handles buffer without newline (last line)
 * - Copies data until newline or end
 *
 * @note
 * - Does not modify source buffer
 * - Caller owns returned string
 */
char	*extract_line(char *buffer)
{
	char	*line;
	char	*ptr;
	size_t	line_len;

	if (!buffer || !buffer[0])
		return (NULL);
	ptr = buffer;
	while (*ptr && (*ptr != '\n'))
		ptr++;
	line_len = ptr - buffer + (*ptr == '\n');
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ptr = line;
	while (line_len--)
		*ptr++ = *buffer++;
	*ptr = '\0';
	return (line);
}

/**
 * @brief Updates buffer after line extraction
 *
 * @param buffer Current buffer (will be freed)
 * @return char* New buffer with remaining content, or NULL if empty/error
 *
 * @details
 * - Allocates new buffer for remaining content
 * - Frees original buffer
 * - Handles cases with/without remaining data
 * - Ensures proper null-termination
 *
 * @note Takes ownership of input buffer, returns new or NULL
 */
char	*update_buffer(char *buffer)
{
	char	*new_buf;
	char	*ptr;
	char	*start;

	if (!buffer)
		return (NULL);
	start = buffer;
	while (*start && *start != '\n')
		start++;
	if (*start == '\n')
		start++;
	if (!*start)
		return (free(buffer), NULL);
	new_buf = malloc(sizeof(char) * (buffer_line_len(start) + 1));
	if (!new_buf)
		return (free(buffer), NULL);
	ptr = new_buf;
	while (*start)
		*ptr++ = *start++;
	*ptr = '\0';
	return (free(buffer), new_buf);
}
