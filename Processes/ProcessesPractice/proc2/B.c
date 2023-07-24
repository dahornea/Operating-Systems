#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

void P1(int fifo, int w){
    int c;
    int num;
    while(read(fifo, &c, sizeof(int)) > 0){
        num = c;
        for(int i = 2; i <= num; i++){
            if(num % i == 0)
                write(w, &i, sizeof(int));
        }
    }
}

void P2(int r){
    int c;
    while(read(r, &c, sizeof(int)) > 0){
        printf("%d ", &c);    
    }
    printf("\n");
}

int main(int argc, char** argv){
    char* fifoName = argv[1];
    int fifo = open(fifoName, O_RDONLY);
    
    int rw[2];
    pipe(rw);
    
    if(fork() == 0){
        close(rw[0]);
        P1(fifo, rw[1]);
        close(rw[1]);
        close(fifo);
        exit(0);
    }
    if(fork() == 0){
        close(rw[1]);
        close(fifo);
        P2(rw[0]);
        close(rw[0]);
        exit(0);
    }
    close(rw[0]);
    close(rw[1]);
    close(fifo);
    unlink(fifoName);
    wait(0);
    wait(0);
    return 0;

}