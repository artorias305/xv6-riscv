#include "kernel/fcntl.h"
#include "user/user.h"

char separators[] = " -\r\t\n./,";

int is_separator(char c)
{
    return strchr(separators, c) != 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(2, "usage: sixfive file...\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            fprintf(2, "sixfive: cannot open %s\n", argv[i]);
            continue;
        }
        char c;
        int num = 0;
        int in_number = 0;

        while (read(fd, &c, 1) == 1) {
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                in_number = 1;
            } else if (is_separator(c)) {
                if (in_number) {
                    if (num % 5 == 0 || num % 6 == 0) {
                        printf("%d\n", num);
                    }
                }
                num = 0;
                in_number = 0;
            } else {
                num = 0;
                in_number = 0;
            }
        }

        // EOF counts as a separator
        if (in_number) {
            if (num % 5 == 0 || num % 6 == 0) {
                printf("%d\n", num);
            }
        }

        close(fd);
    }
    exit(0);
}