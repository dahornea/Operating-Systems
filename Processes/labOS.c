#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv){
    int f = fork();
    pipe(rw);
    int rw[2];
    if(f<0){
        perror("Unable to create process");
        exit(1);
    }
    else if(f==0) { ///child
        close rw[1];
        int nr;
        int nr2;
        read(rw[0], &nr, sizeof(int));
        printf("nr=  %d\n", nr);
        read(rw[0], &nr2, sizeof(int));
        printf("nr2=%d\n", nr2);
        close(rw[0]);
        exit(0);        
    }
    int n;
    printf("N= ");
    scanf("%d", &n);
    int n2;
    printf("n2= ");
    scanf("%d", &n2);
    close(rw[0]);
    write(rw[1], &n, sizeof(int));
    write(rw[1], &n2, sizeof(int));
    close(rw[1]);
    wait(0);
    
    
    return 0;
}