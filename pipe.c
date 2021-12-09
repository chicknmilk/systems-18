#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

char toupper(char str) {
  int i;
  for (i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 32;
  }
}

int main() {
  int fds1[2];
  int fds2[2];

  pipe(fds1);
  pipe(fds2);

  int pid = fork();

  while (1) {
    if (pid == 0) {
      close(fds1[READ]);
      close(fds2[WRITE]);

      char buffer[1024];
      printf("Send something to child process: ");
      fgets(buffer, 1024, stdin);

      write(fds1[WRITE], buffer, strlen(buffer));

      read(fds2[READ], buffer, 1024);
      printf("Child process returned: %s\n", buffer);
    }
    else {
      close(fds1[WRITE]);
      close(fds2[READ]);

      char buffer[1024];
      read(fds1[READ], buffer, 1024);

      int i;
      for (i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '\n') break;
        buffer[i] = toupper(buffer[i]);
      }

      write(fds2[WRITE], buffer, strlen(buffer));
    }
  }
}