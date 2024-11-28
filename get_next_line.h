/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:50:29 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/28 12:05:51 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Header Guard */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Required libraries */
# include <stdlib.h> // malloc, free
# include <unistd.h> // read

/* Buffer size for reading */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// FUNCTIONS
/* Core */
char	*get_next_line(int fd);

/* Buffer management */
char	*join_buffers(char *existing, char *new_data);
char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read);
char	*read_to_buffer(int fd, char *buffer);

/* String utility */
int		find_newline(char *buffer);
size_t	buffer_line_len(char *buffer);

/* Line processing */
char	*extract_line(char *buffer);
char	*update_buffer(char *buffer);

#endif
