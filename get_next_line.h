/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:50:29 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 08:57:48 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Header Guard */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Standard Issue Equipment */
// For malloc, free
# include <stdlib.h>
// For read
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* Main Mission Control */
char	*get_next_line(int fd);

/* Support Operations */
// Buffer Operations
char	*read_to_buffer(int fd, char *buffer);
char	*extract_line(char *buffer);
char	*update_buffer(char *buffer);

// Memory Operations
char	*join_buffers(char *s1, char *s2);
size_t	buffer_len(const char *buffer);

#endif
