/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:30:14 by go-donne          #+#    #+#             */
/*   Updated: 2024/12/11 14:29:20 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_buffers(char *existing, char *new_data)
{
	char	*combined;
	char	*ptr;
	char	*start;

	if (!new_data)
		return (existing);
	combined = malloc(sizeof(char)
			* ((buffer_line_len(existing) + buffer_line_len(new_data)) + 1));
	if (!combined)
		return (free(existing), NULL);
	ptr = combined;
	start = existing;
	while (existing && *existing)
		*ptr++ = *existing++;
	while (new_data && *new_data)
		*ptr++ = *new_data++;
	*ptr = '\0';
	free (start);
	return (combined);
}

char	*process_read(char *buffer, char *temp_buf, ssize_t bytes_read)
{
	if (bytes_read < 0)
		return (free(buffer), NULL);
	if (bytes_read == 0)
	{
		if (!buffer || !buffer[0])
			return (NULL);
		return (buffer);
	}
	temp_buf[bytes_read] = '\0';
	return (join_buffers(buffer, temp_buf));
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buf;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	temp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (free(buffer), NULL);
	while (!find_newline(buffer))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		buffer = process_read(buffer, temp_buf, bytes_read);
		if (!buffer || bytes_read <= 0)
			break ;
	}
	free(temp_buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (free (buffer), buffer = NULL, NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
		return (free (buffer), buffer = NULL, NULL);
	buffer = update_buffer(buffer);
	return (line);
}

/*

#include "get_next_line.h" // For get_next_line
#include <fcntl.h>  // For open, O_RDONLY
#include <stdio.h>  // For printf

// Compilation command:
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -g get_next_line.c
//		get_next_line_utils.c test_gnl.c -o gnl_test
// or: cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c

void test_case(const char *test_name, const char *file_path)
{
    int fd;
    char *line;
    int line_count = 0;

    printf("\nTesting: %s\n", test_name);

	// Open file: establish read-only connection (typically assigns lowest
	// available fd, usually starting at 3 if no other files are open)
    fd = open(file_path, O_RDONLY);

    if (fd < 0)
	{
        printf("Error: Could not open %s\n", file_path);
        return;
    }

	// Main testing loop:
    while ((line = get_next_line(fd))) // Get lines until NULL returned
    {
        printf("Line %d (raw): ", ++line_count);
		 // Print each character, showing \n symbolically
        char *ptr = line;
        while (*ptr)
        {
            if (*ptr == '\n')
                printf("\\n");
            else
                printf("%c", *ptr);
            ptr++;
        }
        printf("\n");  // New line for formatting
        free(line);
    }
    close(fd); // Clean up - release the file descriptor
    printf("Total lines: %d\n", line_count);
}

void	test_invalid_fd(void)
{
	char	*line;

	// Showing NULL symbolically (explicit when gnl returns NULL)

	// Negative fd: guaranteed invalid
	line = get_next_line(-1);
	printf("Result with fd=-1: %s\n", line ? line: "NULL");

	// High fd: most likely invalid (unopened):
	// could however theoretically be in use & valid, hence freeing)
    line = get_next_line(101);
    printf("Result with fd=101: %s\n", line ? line : "NULL");
}

void test_stdin(void)
{
    char *line;
    int line_count = 0;

    while ((line = get_next_line(0)))
    {
        printf("Line %d: ", ++line_count);
        char *ptr = line;
        while (*ptr)
        {
            if (*ptr == '\n')
                printf("\\n");
            else
                printf("%c", *ptr);
            ptr++;
        }
        printf("\n");
        free(line);
    }
    printf("\nTotal lines read from stdin: %d\n", line_count);
}

int main(void)
{
	printf("\n=========================================\n");
    printf("GET_NEXT_LINE TESTING SUITE\n");
    printf("=========================================\n");
	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
    printf("Output Format: Raw output shown with \\n
			representing actual newlines\n");
    printf("=========================================\n");

	printf("\n\n1: BASIC CASES\n");
    printf("Testing standard files with various content patterns\n");
	test_case("Basic Test", "test_basic.txt");
	test_case("Long Lines", "test_long.txt");
    test_case("Empty File", "test_empty.txt");

	printf("\n\n\n2: EDGE CASES\n");
    printf("Testing boundary conditions and special cases\n");
	test_case("No Newline", "test_no_newline.txt");
	test_case("Multiple Empty Lines", "test_empty_lines.txt");

	printf("\n\n\n3: INVALID FD TESTS\n");
	printf("Testing behavior with invalid file descriptors\n");
	test_invalid_fd();

	printf("\n\n\n4: STANDARD INPUT TEST\n");
	printf("Testing stdin (fd 0). Enter text lines:\n");
    printf("- Press Enter after each line\n");
    printf("- Press Ctrl+D to finish\n\n");
	test_stdin();

    return (0);
}
*/
