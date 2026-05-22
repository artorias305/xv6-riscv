#include "user/user.h"

void memdump(char *fmt, char *data)
{
    while (*fmt != '\0') {
        char f = *fmt;
        switch (f) {
            case 'i':
            printf("%d\n", *(int *)data);
            data += 4;
            break;
            case 'p':
            printf("%lx\n", (unsigned long)(*(uint64 *)data));
            data += 8;
            break;
            case 'h':
            printf("%d\n", *(short *)data);
            data += 2;
            break;
            case 's': {
                char *str = (char *)(*(uint64 *)data);
                printf("%s\n", str);
                data += 8;
                break;
            }
            case 'S':
            printf("%s\n", data);
            return;
        }
        fmt++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        int x[2] = {61810, 2025};

        printf("Example 1:\n");
        memdump("ii", (char*)x);

        char *str = "a string";

        printf("Example 2:\n");
        memdump("s", (char*)&str);

        printf("Example 3:\n");
        memdump("S", "another");
    } else if (argc == 2) {
        char buf[1024];
        int n = read(0, buf, sizeof(buf));

        if (n < 0) {
            fprintf(2, "read error\n");
            exit(1);
        }

        memdump(argv[1], buf);
    } else {
        fprintf(2, "usage: memdump [format]\n");
        exit(1);
    }
    exit(0);
}