#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

// Utility function to create test files
void create_test_file(const char *filename, const char *content) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return;
    write(fd, content, strlen(content));
    close(fd);
}

// Test function with result reporting
void run_test(const char *test_name, const char *file_content,
             const char **expected_lines) {
    printf("\n=== Testing: %s ===\n", test_name);

    // Create test file
    create_test_file("test.txt", file_content);

    // Open file
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error: Could not open test file\n");
        return;
    }

    // Read lines and compare
    char *line;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        if (expected_lines[i] == NULL) {
            printf("❌ Test failed: Got extra line: '%s'\n", line);
            free(line);
            break;
        }

        if (strcmp(line, expected_lines[i]) != 0) {
            printf("❌ Test failed:\n");
            printf("Expected: '%s'\n", expected_lines[i]);
            printf("Got:      '%s'\n", line);
        } else {
            printf("✓ Line %d correct: '%s'\n", i + 1, line);
        }

        free(line);
        i++;
    }

    if (expected_lines[i] != NULL) {
        printf("❌ Test failed: Missing expected line: '%s'\n",
               expected_lines[i]);
    }

    close(fd);
}

int main(void) {
    // Test 1: Normal lines
    {
        const char *content = "Hello, world!\nThis is a test.\nLast line.\n";
        const char *expected[] = {
            "Hello, world!\n",
            "This is a test.\n",
            "Last line.\n",
            NULL
        };
        run_test("Normal Lines", content, expected);
    }

    // Test 2: No newline at EOF
    {
        const char *content = "First line\nSecond line\nNo newline here";
        const char *expected[] = {
            "First line\n",
            "Second line\n",
            "No newline here",
            NULL
        };
        run_test("No Newline at EOF", content, expected);
    }

    // Test 3: Empty lines
    {
        const char *content = "\n\nThird line\n";
        const char *expected[] = {
            "\n",
            "\n",
            "Third line\n",
            NULL
        };
        run_test("Empty Lines", content, expected);
    }

    // Test 4: Single character lines
    {
        const char *content = "a\nb\nc\n";
        const char *expected[] = {
            "a\n",
            "b\n",
            "c\n",
            NULL
        };
        run_test("Single Character Lines", content, expected);
    }

    // Test 5: Long line
    {
        char long_line[1000] = {0};
        memset(long_line, 'A', 998);
        strcat(long_line, "\n");
        const char *expected[] = {long_line, NULL};
        run_test("Long Line", long_line, expected);
    }

    // Test 6: Mixed line lengths
    {
        const char *content = "Short\nVery very very long line here\n"
                            "Another short\nEnd";
        const char *expected[] = {
            "Short\n",
            "Very very very long line here\n",
            "Another short\n",
            "End",
            NULL
        };
        run_test("Mixed Line Lengths", content, expected);
    }

    // Test 7: Empty file
    {
        const char *content = "";
        const char *expected[] = {NULL};
        run_test("Empty File", content, expected);
    }

    // Test 8: Multi-line poetry (tests aesthetics and various lengths)
    {
        const char *content =
            "Do not go gentle into that good night,\n"
            "Old age should burn and rave at close of day;\n"
            "Rage, rage against the dying of the light.\n";
        const char *expected[] = {
            "Do not go gentle into that good night,\n",
            "Old age should burn and rave at close of day;\n",
            "Rage, rage against the dying of the light.\n",
            NULL
        };
        run_test("Poetry Test", content, expected);
    }

    printf("\nTest suite completed.\n");
    return 0;
}
