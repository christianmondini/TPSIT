#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int f1, f2, g, h, padre;
    padre = getpid();
    f1 = 0;
    f2 = 0;
    g = 0;
    h = 0;
    printf("1) processo padre con pid: %i\n", padre);
    f1 = fork(); //nasce il primo figlio
    if (f1 > 0)  //processo figlio
    {
        printf("2) processo figlio 1 con pid: %i\n", f1);
        f2 = fork(); //nasce il secondo figlio
        if (f2 > 0)
        {
            printf("4) processo figlio 2 con pid: %i\n", f2);
            waitpid(f2, 0, 0);
            printf("8) ha terminato F2: %i \n", f2);
            waitpid(f1, 0, 0);
            printf("9) ha terminato F1: %i \n", f1);
        }
        else if (f2 == 0)
        {
            h = fork(); //nipote 2
            if (h == 0)
                exit(0);
            else
            {
                printf("5) processo nipote 2 con pid: %i \n", h);
                waitpid(h, 0, 0);
                printf("7) ha terminato N2: %i \n", h);
                exit(0);
            }
        }
    }
    else if (f1 == 0) //figlio 1
    {
        g = fork(); //nipote 1
        if (g == 0)
            exit(0);
        else
        {
            printf("3) processo nipote 1 con pid: %i \n", g);
            waitpid(g, 0, 0);
            printf("6) ha terminato N1: %i \n", g);
            exit(0);
        }
    }
    return 0;
}