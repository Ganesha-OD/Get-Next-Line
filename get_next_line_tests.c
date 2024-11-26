#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/* Test Helper Functions */
void test_header(const char *test_name)
{
    printf("\n=== %s ===\n", test_name);
}

void test_result(const char *test_name, int success)
{
    printf("%s: %s\n", test_name, success ? "PASS ✓" : "FAIL ✗");
}

/* Test Cases */
void test_basic_read(void)
{
    test_header("Basic Read Operation");

    int fd = open("test_files/single_line.txt", O_RDONLY);
    if (fd < 0)
    {
        test_result("File Open", 0);
        return;
    }
    test_result("File Open", 1);

    char *buffer = NULL;
    buffer = read_to_buffer(fd, buffer);

    test_result("Read Operation", buffer != NULL);
    test_result("Content Check", buffer && strstr(buffer, "Hello, quantum realm!") != NULL);

    free(buffer);
    close(fd);
}

void test_buffer_joining(void)
{
    test_header("Buffer Joining");

    char *str1 = strdup("Hello, ");
    char *str2 = "quantum realm!";

    char *result = join_buffers(str1, str2);
    test_result("Join Operation", result != NULL);
    test_result("Content Check", result && strcmp(result, "Hello, quantum realm!") == 0);

    free(str1);
    free(result);
}

void test_newline_detection(void)
{
    test_header("Newline Detection");

    char *with_nl = "test\n";
    char *without_nl = "test";

    test_result("Find Newline Present", find_newline(with_nl) == 1);
    test_result("Find Newline Absent", find_newline(without_nl) == 0);
    test_result("Find Newline NULL", find_newline(NULL) == 0);
}

void test_buffer_length(void)
{
    test_header("Buffer Length");

    char *test_str = "Hello";

    test_result("Length Check", buffer_length(test_str) == 5);
    test_result("Empty String", buffer_length("") == 0);
    test_result("NULL Check", buffer_length(NULL) == 0);
}

/* Main Test Runner */
int main(void)
{
    printf("\nQuantum Interceptor Phase 2 Test Suite\n");
    printf("=====================================\n");

    /* Create test files */
    system("mkdir -p test_files");

    FILE *f1 = fopen("test_files/single_line.txt", "w");
    fprintf(f1, "Hello, quantum realm!\n");
    fclose(f1);

    /* Run tests */
    test_basic_read();
    test_buffer_joining();
    test_newline_detection();
    test_buffer_length();

    printf("\nTest Suite Complete!\n");
    return 0;
}
