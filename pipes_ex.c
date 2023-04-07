#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* https://www.youtube.com/watch?v=Mqb2dVRe0uo */

int main(int argc, char *argv[]) {
  int fd[2];
  // fd[0] - read
  // fd[1] - write
  if (pipe(fd) == -1) {
    perror("pipe error");
    exit(1);
  }
  int id = fork();
  if (id == 0) {
    close(fd[0]);
    int x;
    printf("Input a number: ");
    scanf("%d", &x);
    if (write(fd[1], &x, sizeof(int)) == -1) {
      perror("write error");
      exit(2);
    }
    close(fd[1]);
  } else {
    close(fd[1]);
    int y;
    if (read(fd[0], &y, sizeof(int)) == -1) {
      perror("read error");
      exit(3);
    }
    close(fd[0]);
    printf("Got from child process %d\n", y);
  }

  return EXIT_SUCCESS;
}
