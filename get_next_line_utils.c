/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 12:48:05 by go-donne         ###   ########.fr       */
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
        if (buffer[i] == '\n')
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

/* Other function shells for Phase 2 */

char	*extract_line(char *buffer)
{
	(void)buffer;
	return (NULL);
}

char	*update_buffer(char *buffer)
{
	(void)buffer;
	return (NULL);
}
