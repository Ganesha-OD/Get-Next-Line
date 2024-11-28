/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/27 13:48:57 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
