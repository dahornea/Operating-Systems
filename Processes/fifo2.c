#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
    char * name = argv[1];
    int fd = open(name, O_RDONLY);
    if(fd < 0){
        perror("The fifo was not opened");
        exit(1);
    }

    int sz;
    char *str;
    read(fd, &sz, sizeof(int));
    str = malloc(sz* sizeof(char));
    read(fd, str, sizeof(char)*sz);
    printf("%d\n", sz);
    printf("%s\n", str);
    free(str);
    return 0;    
}