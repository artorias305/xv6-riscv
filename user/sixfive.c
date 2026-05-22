#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char **argv)
{
    char *file;
    if (argc == 1) {
        fprintf(2, "Usage: sixfive file1 file2 file3...\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
    }
    exit(0);
}