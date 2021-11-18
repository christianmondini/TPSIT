///  \file   stringToUpper.c
///  \brief  mostra a schermo il carattere/stringa inseriti nel terminale come argomento, in maiuscolo
///  \date   Il file è stato creato l'17/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 *  \fn     int main()
 *  \brief  funzione principale, dove viene istanziato un processo figlio, il quale si occuperà di mettere in maiuscolo, un carattere alla volta, la stringa presente in argv[1]
 *  \param  int argc: contiene il numero di argomenti inseriti dall’utente a linea di comando
 *  \param  char *argv: l’array che contiene le stringhe inserite dall’utente a linea di comando
 *  \return int: indica come è terminato il programma
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("errore nell'inserimento degli argomenti\n");
        exit(1);
    }
    else
    {
        int PID = fork();
        if (PID < 0)
        {
            printf("errore nella generazione del processo figlio\n");
            exit(2);
        }
        else if (PID == 0) //processo figlio
        {
            printf("Figlio: Inizio la conversione dei caratteri in minuscolo a maiuscolo\n");
            int dim = strlen(argv[1]);
            for (int i = 0; i < dim; i++)
                argv[1][i] = toupper(argv[1][i]);
            printf("Figlio: %s\n", argv[1]);
            printf("Figlio: Ho terminato\n");
            exit(3);
        }
        else //processo padre
        {
            wait(&PID);
            printf("Padre: Il processo figlio ha terminato\n");
        }
    }

    return 0;
}