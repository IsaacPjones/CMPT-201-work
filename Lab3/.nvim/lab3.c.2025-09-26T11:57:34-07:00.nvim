#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAP 5

// helper function for putting in order and prints
static void print_history(char *history[], int count, int next_index) {
  if (count == 0)
    return;
  int start = (next_index - count + CAP) % CAP;
  for (int i = 0; i < count; i++) {
    char *s = history[(start + i) % CAP];
    if (s)
      puts(s);
  }
}

int main(void) {
  char *line = NULL;
  size_t cap = 0;
  ssize_t len;

  char *history[CAP] = {0};
  int count = 0;
  int next = 0;

  for (;;) {
    printf("Enter input: ");
    fflush(stdout);

    len = getline(&line, &cap, stdin);
    if (len == -1)
      break; // EOF or error -> exit

    if (len > 0 && line[len - 1] == '\n') {
      line[--len] = '\0';
    }

    free(history[next]);
    history[next] = strdup(line);
    if (!history[next]) {
      perror("strdup");
      break;
    }
    next = (next + 1) % CAP;
    if (count < CAP)
      count++;

    if (strcmp(line, "print") == 0) {
      print_history(history, count, next);
    }
  }

  free(line);
  for (int i = 0; i < CAP; i++)
    free(history[i]);
  return 0;
}
