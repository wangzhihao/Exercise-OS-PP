#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ONE_KB 1024

struct timeval begin, end;

void timer_start() {
    gettimeofday(&begin, NULL);
}

void timer_stop() {
    gettimeofday(&end, NULL);
}

suseconds_t timer_diff() {
    return end.tv_usec - begin.tv_usec;
}

int main() {

    timer_start();
    int fd = open("testfile", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO );
    if(fd == -1) {
        perror("fail to create the file.");
        exit(EXIT_FAILURE);
    }
    timer_stop();
    printf("%ld microseconds used to open file.\n", timer_diff());

    char buf[ONE_KB]; //1KB
    memset(buf, 'a', sizeof(buf));

    timer_start();
    int i, result;
    for(i = 0; i< 100; i++)
    {
        result =  write(fd, buf, sizeof(buf));
        if(result == -1) {
            perror("fail to write the buffer.");
            exit(EXIT_FAILURE);
        }
    }
    timer_stop();
    printf("%ld microseconds used to write 100KB data.\n", timer_diff());

    timer_start();
    result = close(fd);
    if(result == -1) {
        perror("fail to close the file.");
        exit(EXIT_FAILURE);
    }
    timer_stop();
    printf("%ld microseconds used to close file.\n", timer_diff());

    return 0;
}
