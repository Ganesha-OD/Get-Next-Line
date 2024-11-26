/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 12:25:54 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Find Newline in Buffer */
int find_newline(char *buffer)
{
    size_t i;

    i = 0;
    if (!buffer)
        return (0);
    while (buffer[i])
    {
        if (buffer[i] == '\\n')
            return (1);
        i++;
    }
    return (0);
}

/* Get Buffer Length */
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

char	*read_to_buffer(int fd, char *buffer)
{
	/* Phase 1: Minimal implementation */
	char	*temp;
	ssize_t	bytes_read;

	/* Just basic read to prove concept */
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (NULL);
	}
	temp[bytes_read] = '\\0';
	return (temp);
}
/* Other function shells for Phase 2 */

char	*extract_line(char *buffer)
{
	return (NULL);
}

char	*update_buffer(char *buffer)
{
	return (NULL);
}
