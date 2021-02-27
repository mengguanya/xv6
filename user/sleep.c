#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int parse_int(const char* arg) {
    const char* p = arg;
    for (; *p; p ++) {
        if (*p < '0' || *p > '9') {
            return -1;
        }
    }
    return atoi(arg);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: sleep seconds\n");
        exit(1);
    }
    int time = parse_int(argv[1]);
    if (time < 0) {
        printf("Error argument : %s\n", argv[1]);
        exit(0);
    }
    sleep(time);
    exit(0);
}
