#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clear_screen()
{
    printf("\033[H\033[J");
}

int get_cpu_count()
{
    system("lscpu | grep '^CPU(s):' | awk '{print $2}' > core_config.tmp");
    
    FILE *f = fopen("core_config.tmp", "r");
    if (!f) return 1;
    
    int cores;
    fscanf(f, "%d", &cores);
    fclose(f);
    system("rm core_config.tmp");
    return (cores > 0) ? cores : 1;
}

int main()
{
    int choice;
    int start, end, cores, max_cores;
    char command[512];

    while (1)
    {
        clear_screen();
        printf("============================================\n");
        printf("   PRIME BENCHMARK (Manual Build Mode)      \n");
        printf("============================================\n");
        printf("1. Run Benchmark (Text Output)\n");
        printf("2. Run Auto-Scaling Test (1 to N Cores)\n");
        printf("3. Generate Graph (Python Plotter)\n");
        printf("4. Exit\n");
        printf("============================================\n");
        printf("Select Option: ");
        
        if(scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n'); 
            continue;
        }

        if(choice == 1)
        {
            printf("\n--- Run Benchmark ---\n");
            printf("Start Range: ");
            scanf("%d", &start);
            printf("End Range: ");
            scanf("%d", &end);
            printf("Cores: ");
            scanf("%d", &cores);
            
            sprintf(command, "./prime_app %d %d %d", start, end, cores);
            system(command);
            
            printf("\n[Success] Check 'prime.txt'.\n");
            system("head -n 5 prime.txt");

        }
        else if(choice == 2)
        {
            printf("\n--- Auto-Scaling Benchmark ---\n");
            printf("Start Range: ");
            scanf("%d", &start);
            printf("End Range: ");
            scanf("%d", &end);
            
            printf("[System] Detecting Hardware...\n");
            max_cores = get_cpu_count();
            printf("[System] Found %d Logical Cores.\n\n", max_cores);
            printf("Running benchmarks from 1 to %d cores:\n", max_cores);
            printf("--------------------------------------\n");

            for (int i=1;i<=max_cores;i++)
            {
                printf("Cores: %2d | Time: ", i); 
                fflush(stdout);
                sprintf(command, "./prime_app %d %d %d", start, end, i);
                system(command);
                printf(" s\n");
            }
            printf("--------------------------------------\n");
            printf("[Done] All tests completed.\n");
        }
        else if(choice == 3)
        {
            printf("\n--- Generate Graph ---\n");
            printf("Start Range: "); scanf("%d", &start);
            printf("End Range: ");   scanf("%d", &end);
            printf("Max Cores: ");   scanf("%d", &cores);
            sprintf(command, "python3 plotter.py %d %d %d", start, end, cores);
            system(command);

        }
        else if (choice == 4)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
        {
            printf("Invalid option.\n");
        }

        printf("\nPress Enter to return to menu...");
        getchar();
        getchar(); 
    }
    return 0;
}