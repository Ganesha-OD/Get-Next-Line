#include "get_next_line.h" // For get_next_line
#include <fcntl.h>  // For open, O_RDONLY
#include <stdio.h>  // For printf

void test_case(const char *test_name, const char *file_path)
{
    int fd;
    char *line;
    int line_count = 0;

    printf("\nTesting: %s\n", test_name);

	// Open file:
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

int main(void)
{
	// Print buffer size being used
    printf("Starting GNL tests with BUFFER_SIZE=%d\n", BUFFER_SIZE);

	// Run tests on different files

	// Basic Cases
	test_case("Basic Test", "test_basic.txt");
	test_case("Long Lines", "test_long.txt");
    test_case("Empty File", "test_empty.txt");

	//Edge Cases
	test_case("No Newline", "test_no_newline.txt");
	test_case("Multiple Empty Lines", "test_empty_lines.txt");

    return (0);
}
