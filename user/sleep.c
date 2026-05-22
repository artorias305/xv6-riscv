#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int time;
  if (argc != 2) {
    fprintf(2, "Usage: sleep <time>\n");
    exit(1);
  }
  time = atoi(argv[1]);
  if (time > 0) pause(time);
  else {
    fprintf(2, "invalid time\n");
    exit(1);
  }
  exit(0);
}
