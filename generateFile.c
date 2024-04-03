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
    fprintf(stderr, "Benutzung: %s <Dateiname> <String>\n", argv[0]);
    return 1;
  }

  int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0640);
  if (fd == -1) {
    fprintf(stderr, "Fehler: Datei konnte nicht geöffnet werden.\n");
    return 1;
  }

  size_t bytes_written = write(fd, argv[2], strlen(argv[2]));
  if (bytes_written == -1) {
    fprintf(stderr, "Fehler: Fehler beim Schreiben in die Datei.\n");
    return 1;
  }

  close(fd);

  return 0;
}
