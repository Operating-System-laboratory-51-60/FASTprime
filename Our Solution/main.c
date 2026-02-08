#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include "primes.h"

int main(int argc,char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <start> <end> <cores>\n", argv[0]);
        return 1;
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int cores = atoi(argv[3]);
    int range_len = end-start + 1;
    int chunk = range_len / cores;

    struct timeval t1,t2;
    gettimeofday(&t1,NULL);

    // Forking Loop
    for (int i=0;i<cores;i++)
    {
        int r_start = start+i*chunk;
        int r_end = (i==cores-1) ? end : (r_start+chunk-1);
        
        pid_t pid = fork();
        
        if (pid == 0)
        {   // Child
            char filename[20];
            sprintf(filename, "part_%d.tmp", i);
            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            solve_range(r_start, r_end, fd);
            close(fd);
            exit(0);
        }
    }

    // Wait for all children
    for(int i=0;i<cores;i++) wait(NULL);

    // Merge files
    system("cat part_*.tmp > prime.txt && rm part_*.tmp");

    gettimeofday(&t2,NULL);
    double elapsed = (t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec) / 1000000.0;
    
    // Output only the time for the python script to read
    printf("%f", elapsed); 
    return 0;
}