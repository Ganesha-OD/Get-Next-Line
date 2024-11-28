#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // First test with a simple file
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return (1);
    }

    // Read lines until get_next_line returns NULL
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }

    close(fd);
    return (0);
}
