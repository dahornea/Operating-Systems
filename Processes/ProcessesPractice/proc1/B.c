#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <sys/wait.h>

// FIRST CHILD: CALCULATE SUM
// READ CHARS FROM FIFO, WRITE SUM TO PIPE
void P1(int fifo, int w)
{
    char c;
    int num;
    
    // READ CHAR BY CHAR UNTIL DONE
    int sum = 0;
    while(read(fifo, &c, sizeof(char)) > 0)
    {
        // SUBSTRACT CHAR '0' TO OBTAIN INTEGER
        num = c - '0';
        sum += num;
    }
    
    // WRITE TO PIPE
    write(w, &sum, sizeof(int));
}

// SECOND CHILD: PRINT DIVISORS
// READ FROM PIPE
void P2(int r)
{
    // READ SUM
    int sum;
    read(r, &sum, sizeof(int));
    
    // LOOP NUMBER, PRINT DIVISORS
    for (int i = 1; i <= sum; i++)
    {
        if (sum % i == 0)
        {
            printf("%d ", i);
        }
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    // SET THE FIFO NAME TO THE FIRST ARGUMENT
    // OPEN THE FIFO
    char* fifoName = argv[1];
    int fifo = open(fifoName, O_RDONLY);
    
    // CREATE PIPE
    int rw[2];
    pipe(rw);

    // CREATE FIRST CHILD
    // CLOSE EVERYTHING TO PREVENT LEAKS
    if (fork() == 0)
    {
        close(rw[0]);
        P1(fifo, rw[1]);

        close(rw[1]);
        close(fifo);

        // KILL CHILD (PREVENT RUNNING EXTRA CODE)
        exit(0);
    }
    
    // CREATE SECOND CHILD
    // CLOSE EVERYTHING TO PREVENT LEAKS
    if (fork() == 0)
    {
        close(rw[1]);
        close(fifo);

        P2(rw[0]);
        close(rw[0]);

        // KILL CHILD (PREVENT RUNNING EXTRA CODE)
        exit(0);
    }
    
    // BACK TO PARENT
    // CLOSE EVERYTHING TO PREVENT LEAKS
    close(rw[0]);
    close(rw[1]);

    close(fifo);
    unlink(fifoName); // DELETE FIFO

    // WAIT FOR CHILDREN TO FINISH TO PREVENT ZOMBIES
    wait(0);
    wait(0);
    return 0;
}
