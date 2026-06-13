#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
readline(int fd, char *buf, int size)
{
  char c;
  int i = 0;

  while ((i < size - 1) && read(fd, &c, 1) > 0) {
    if (c == '\n') {
      buf[i] = '\0';
      return i + 1;
    } else
      buf[i] = c;
    i++;
  }

  buf[i] = '\0';

  while (read(fd, &c, 1) > 0 && c != '\n')
    ;

  return i;
}

int
main(int argc, char *argv[])
{
  char buf[512];
  char *args[MAXARG];

  if (argc < 2) {
    fprintf(2, "usage: xargs command [args...]\n");
    exit(1);
  }

  while (readline(0, buf, sizeof(buf))) {
    int pid = fork();

    if (pid < 0) {
      fprintf(2, "xargs: fork failed\n");
      exit(1);
    } else if (pid == 0) {
      // child process
      for (int i = 0; i < argc - 1; i++)
        args[i] = argv[i + 1];
      args[argc - 1] = buf;
      args[argc] = 0;

      exec(args[0], args);
      fprintf(2, "xargs: exec %s failed\n", args[0]);
      exit(1);
    } else {
      wait(0); // wait for child to finish
    }
  }

  exit(0);
}
