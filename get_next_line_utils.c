/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/27 09:45:27 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*handle_error(char *to_free, char *extra_to_free)
// {
// 	if (to_free)
// 		free(to_free);
// 	if (extra_to_free)
// 		free (extra_to_free);
// 	return (NULL);
// }

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

size_t buffer_line_len(char *buffer)
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
	size_t	line_len;
	size_t	i;

	if (!buffer || !buffer[0])
		return (NULL);
	line_len = 0;
	while (buffer[line_len] && (buffer[line_len] != '\n'))
		line_len++;
	if (buffer[line_len] == '\n')
		line_len++;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char *buffer)
{
	char	*new_buf;
	size_t	start;
	size_t	i;

	if (!buffer)
		return (NULL);
	start = 0;
	while (buffer[start] && (buffer[start] != '\n'))
		start++;
	if (buffer[start] == '\n')
		start++;
	if (!buffer[start])
		return (handle_error(buffer, NULL));
	new_buf = malloc(sizeof(char) * (buffer_line_len(buffer) - start + 1));
	if (!new_buf)
		return (handle_error(buffer, NULL));
	i = 0;
	while (buffer[start])
		new_buf[i++] = buffer[start++];
	new_buf[i] = '\0';
	return (handle_error(buffer, NULL), new_buf);
}
