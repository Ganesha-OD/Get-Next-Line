/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:50:29 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/26 17:15:00 by go-donne         ###   ########.fr       */
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
char	*join_buffers(char *existing, char *new_data);
char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read);
char	*read_to_buffer(int fd, char *buffer);
char	*handle_error(char *to_free, char *extra_to_free);
int		find_newline(char *buffer);
size_t	buffer_line_len(char *buffer);
char	*extract_line(char *buffer);
char	*update_buffer(char *buffer);

#endif
