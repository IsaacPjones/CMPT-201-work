#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  while (1) {
    printf("Enter program to run.\n>");
    fflush(stdout);

    ssize_t len = getline(&line, &cap, stdin);

    if (len == -1) {
      puts("EOF or error");
      break;
    }

    if (len > 0 &&
        line[len - 1] == '\n') { // replaces new line with null terminator
      line[len - 1] = '\0';
    }

    char *path = strdup(line);
    if (!path) {
      perror("strdup");
      continue;
    }

    char *saveptr;
    char *token = strtok_r(line, "/", &saveptr);
    char *last = token;

    while (token != NULL) {
      last = token;
      token = strtok_r(NULL, "/", &saveptr);
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      free(path);
      continue;
    }

    if (pid == 0) { // Child case
      execl(path, last, (char *)NULL);
      perror("execl");
      _exit(1);
    } else {
      int status;
      waitpid(pid, &status, 0);
      free(path);
    }
  }
  free(line);
  return 0;
}
