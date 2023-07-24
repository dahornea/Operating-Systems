#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    int nr1;
    int nr2;
    printf("Enter the first number: ");
    scanf("%d", &nr1);
    printf("Enter the second number: ");
    scanf("%d", &nr2);
    char* fifoName = argv[1];
    mkfifo(fifoName, 0600);
    int fifo = open(fifoName, O_WRONLY);
    int cmmmc;
    int cmmdc;
    for(int i = 1; i <= nr1 && i <= nr2; i++){
        if(nr1 % i == 0 && nr2 % i == 0){
            cmmdc = i;
        }    
    }
    cmmmc = (nr1 * nr2) / cmmdc;
    write(fifo, &cmmmc, sizeof(int));
    close(fifo);
    return 0;
}