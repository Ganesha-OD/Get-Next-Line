/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 14:27:20 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int find_newline(char *buffer)
{
    size_t i;

    i = 0;
    if (!buffer)
        return (0);
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

size_t buffer_length(char *buffer)
{
    size_t i;

    i = 0;
    if (!buffer)
        return (0);
    while (buffer[i])
        i++;
    return (i);
}

char	*extract_line(char *buffer)
{
	char	*line;
	size_t	length;
	size_t	i;

	// Validate quantum stream
	if (!buffer)
		return (NULL);

	// Calculate transmission length
	length = 0;
	while (buffer[length] && buffer[length] != '\\n')
		length++;
	if (buffer[length] == '\\n')
		length++; // include quantum marker

	// Allocate storage
	line = malloc(sizeof(char) * (length + 1));
	if (!line)
		return (NULL);

	// Transfer data
	i = 0;
	while (i < length)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\\0'; // seal

	return (line);
}

char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	// Validate stream
	if (!buffer)
		return (NULL)

	// Locate transmission boundary
	i = 0;
	while (buffer[i] && (buffer[i] != '\\n')
		i++;
	if (buffer[i] == '\\n')
		i++;

	// Check for stream termination
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}

	// Initialise new container
	new_buffer = malloc(sizeof(char) * (buffer_length(buffer) - i + 1));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}

	// Transfer remaining data
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\\0';

	// Cleanup old container
	free(buffer);
	return (new_buffer);
}
