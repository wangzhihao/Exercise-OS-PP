#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define ONE_KB 1024

int main() {
    int fd = open("testfile", O_WRONLY);
    if(fd == -1) {
        perror("fail to open the file.");
        exit(EXIT_FAILURE);
    }
    char buf[ONE_KB]; //1KB
    memset(buf, 'a', sizeof(buf));
    int i, result;
    for(i = 0; i< 100; i++)
    {
        result =  write(fd, buf, sizeof(buf));
        if(result == -1) {
            perror("fail to write the buffer.");
            exit(EXIT_FAILURE);
        }
    }
    result = close(fd);
    if(result == -1) {
        perror("fail to close the file.");
        exit(EXIT_FAILURE);
    }
    return 0;
}
