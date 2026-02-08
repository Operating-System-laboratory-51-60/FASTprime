#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clear_screen()
{
    printf("\033[H\033[J");
}

int main()
{
    int choice;
    int start, end, cores;
    char command[512];

    while (1)
    {
        clear_screen();
        printf("============================================\n");
        printf("   PRIME BENCHMARK (Manual Build Mode)      \n");
        printf("============================================\n");
        printf("1. Run Benchmark (Text Output)\n");
        printf("2. Generate Graph (Python Plotter)\n");
        printf("3. Exit\n");
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
            printf("\n--- Generate Graph ---\n");
            printf("Start Range: "); scanf("%d", &start);
            printf("End Range: ");   scanf("%d", &end);
            printf("Max Cores: ");   scanf("%d", &cores);
            sprintf(command, "python3 plotter.py %d %d %d", start, end, cores);
            system(command);

        }
        else if (choice == 3)
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
