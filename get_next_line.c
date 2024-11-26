/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:30:14 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 12:25:32 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// BUFFER JOINING OPERATION

char *join_buffers(char *existing, char *new_data)
{
    char    *combined;
    size_t  total_length;
    size_t  i;
    size_t  j;

    /* Calculate Combined Length */
    total_length = buffer_length(existing) + buffer_length(new_data);

    /* Allocate Combined Space */
    combined = malloc(sizeof(char) * (total_length + 1));
    if (!combined)
        return (NULL);

    /* Copy Existing Data */
    i = 0;
    if (existing)
    {
        while (existing[i])
        {
            combined[i] = existing[i];
            i++;
        }
    }

    /* Append New Data */
    j = 0;
    while (new_data[j])
        combined[i++] = new_data[j++];

    /* Terminate Combined Data */
    combined[i] = '\\0';

    return (combined);
}



// READ TO BUFFER: CORE DESIGN

char *read_to_buffer(int fd, char *buffer)
{
    char    *quantum_receiver;  // Temporary reception bay
    char    *merged_data;       // Combined transmissions
    ssize_t bytes_received;     // Reception status

    /* Initialize Reception Equipment */
    quantum_receiver = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!quantum_receiver)
        return (NULL);

    /* Quantum Reception Loop */
    while (1)
    {
        /* Attempt Reception */
        bytes_received = read(fd, quantum_receiver, BUFFER_SIZE);

        /* Check Reception Status */
        if (bytes_received < 0)  // Reception error
        {
            free(quantum_receiver);
            return (free(buffer), NULL);
        }

        if (bytes_received == 0)  // End of transmission
            break;

        /* Mark End of Received Data */
        quantum_receiver[bytes_received] = '\\0';

        /* Merge with Existing Data */
        merged_data = join_buffers(buffer, quantum_receiver);
        if (!merged_data)
        {
            free(quantum_receiver);
            return (free(buffer), NULL);
        }
        free(buffer);  // Clean up old buffer
        buffer = merged_data;

        /* Check for Complete Transmission (\\n) */
        if (find_newline(buffer))
            break;
    }

    /* Clean Up Reception Equipment */
    free(quantum_receiver);
    return (buffer);
}




char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
