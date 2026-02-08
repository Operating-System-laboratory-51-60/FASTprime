/*
 * Purpose: Calculate prime numbers using multiple processes to speed up execution.
 * Method: Uses fork() to create child processes, each handling a chunk of the range.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <sys/time.h>
 #include <fcntl.h>
 
 // Function to check if a number 'n' is prime.
 // Returns 1 if prime, 0 otherwise.
 int check_prime(int n) {
     if (n <= 1) return 0; // 0 and 1 are not prime
     // Loop from 2 up to square root of n
     for (int i = 2; i * i <= n; i++) {
         if (n % i == 0) return 0; // Found a divisor, not prime
     }
     return 1; // No divisors found, it is prime
 }
 
 int main(int argc, char *argv[]) {
     // Check if the user provided enough arguments
     if (argc < 4) {
         printf("Usage: %s <start> <end> <processes>\n", argv[0]);
         return 1;
     }
 
     // Parse command line arguments
     int start = atoi(argv[1]);
     int end = atoi(argv[2]);
     int n_procs = atoi(argv[3]);
 
     // Calculate the size of the range and the chunk size for each process
     int range = end - start + 1;
     int chunk = range / n_procs;
 
     // Structure to measure execution time
     struct timeval t1, t2;
     gettimeofday(&t1, NULL); // Start timer
 
     // Loop to create 'n_procs' child processes
     for (int i = 0; i < n_procs; i++) {
         pid_t pid = fork(); // Create a new process
 
         if (pid == 0) {
             // --- CHILD PROCESS LOGIC ---
             
             // Create a unique temporary filename (e.g., temp_0.txt)
             char fname[20];
             sprintf(fname, "temp_%d.txt", i);
             
             // Open file for writing (Create if not exists, Truncate if exists)
             int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
             
             // Calculate start and end for this specific child
             int r_s = start + i * chunk;
             // The last process takes the remainder of the range
             int r_e = (i == n_procs - 1) ? end : r_s + chunk - 1;
             
             char buf[32];
             // Iterate through the assigned chunk
             for (int num = r_s; num <= r_e; num++) {
                 if (check_prime(num)) {
                     // Convert integer to string and write to file
                     int len = sprintf(buf, "%d\n", num);
                     write(fd, buf, len);
                 }
             }
             
             close(fd); // Close file descriptor
             exit(0);   // Terminate child process
         }
     }
 
     // --- PARENT PROCESS LOGIC ---
 
     // Wait for ALL child processes to finish
     // This ensures we don't merge files before they are written
     while(wait(NULL) > 0);
 
     // Use system shell command to concatenate all temp files into one
     system("cat temp_*.txt > ai_primes.txt");
     
     // Clean up temporary files to keep directory clean
     system("rm temp_*.txt");
 
     // Stop timer
     gettimeofday(&t2, NULL);
     
     // Calculate elapsed time in seconds
     double time_taken = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1e6;
     
     // Output only the time (so Python script can read it easily)
     printf("%f", time_taken);
     
     return 0;
 }