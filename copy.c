#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Fehler: Falsche Anzahl an Argumenten.\n");
        fprintf(stderr, "Benutzung: %s <Quelldatei> <Zieldatei>\n", argv[0]);
    }

    int fd_start = open(argv[1], O_RDONLY, 0640);
    if (fd_start == -1) {
        fprintf(stderr, "Fehler: Quelldatei konnte nicht geöffnet werden.\n");
        return 1;
    }

    if (unlink(argv[2]) == -1);

    int fd_goal = open(argv[2], O_WRONLY | O_CREAT, 0640);
    if (fd_goal == -1) {
        fprintf(stderr, "Fehler: Zieldatei konnte nicht geöffnet werden.\n");
        return 1;
    }

    char c;
    ssize_t bytes_read = 1;
    ssize_t bytes_written = 0;

    while (bytes_read != 0) {
        bytes_read = read(fd_start, &c, 1);
        if (bytes_read == -1) {
            fprintf(stderr, "Fehler: Quelldatei konnte nicht gelesen werden.\n");
            return 1;
        }

        if (bytes_read == 0) {
            break;
        }

        bytes_written = write(fd_goal, &c, 1);
        if (bytes_written == -1) {
            fprintf(stderr, "Fehler: Zieldatei konnte nicht beschrieben werden.\n");
        }
    }

    if (unlink(argv[1]) == -1) {
        fprintf(stderr, "Fehler: Quelldatei konnte nicht überschrieben werden.\n");
    }

    close(fd_start);
    close(fd_goal);

    return 0;

}