#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Fehler: Falsche Anzahl an Argumenten.\n");
        fprintf(stderr, "Benutzung: %s <Dateiname>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY, 0640);
    if (fd == -1) {
        fprintf(stderr, "Fehler: Datei konnte nicht geöffnet werden.\n");
        return 1;
    }

    char c[100];
    int i = 0;
    ssize_t bytes_read = 1;

    while (bytes_read != 0) {
        bytes_read = read(fd, &c[i], 1);
        if (bytes_read == -1) {
            fprintf(stderr, "Fehler: Datei konnte nicht gelesen werden.\n");
            return 1;
        }

        i++;
    }

    if (write(STDOUT_FILENO, &c, 100) == -1) {
        fprintf(stderr, "Fehler: Beim ausgeben.\n");
        return 1;
    }

    printf("\n");

    close(fd);

    return 0;
}
