#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>

void write_to_file(const char *file_path, const char *content) {
    openlog(NULL, LOG_PID | LOG_CONS, LOG_USER);

    // Open the file
    int file_descriptor = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file_descriptor == -1) {
        syslog(LOG_ERR, "Error %d: %s - Failed to open file '%s'\n", errno, strerror(errno), file_path);
        closelog();
        exit(EXIT_FAILURE);
    }

    // Write content to the file
    ssize_t bytes_written = write(file_descriptor, content, strlen(content));

    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error %d: %s - Failed to write to file '%s'\n", errno, strerror(errno), file_path);
        close(file_descriptor);
        closelog();
        exit(EXIT_FAILURE);
    }

    syslog(LOG_DEBUG, "Writing '%s' to '%s'\n", content, file_path);

    // Close the file
    if (close(file_descriptor) == -1) {
        syslog(LOG_ERR, "Error %d: %s - Failed to close file '%s'\n", errno, strerror(errno), file_path);
        closelog();
        exit(EXIT_FAILURE);
    }

    closelog();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_path> <content>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *file_path = argv[1];
    const char *content = argv[2];

    // Create the directory if it doesn't exist (Note: Assumed to be created by the caller)
    // mkdir -p "$(dirname "$file_path")"

    write_to_file(file_path, content);

    return EXIT_SUCCESS;
}

