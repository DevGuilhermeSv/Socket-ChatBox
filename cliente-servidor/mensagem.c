#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char **AlocaMatriz(int m, int n);

char **randon()
{
    char **string = AlocaMatriz(1000000, 5);
    char aux[5];
    puts("gravando numeros");
    for (int y = 0; y < 1000000; y++)
    {

        int a = (rand() % 1001);
        sprintf(aux, "%i", a);
        strncpy(string[y], aux, 5);
    }
    puts("FIM DA GRAVACAO");
    /* for (int y = 0; y < 10; y++)
    {
        printf("y: %d, M: %s \n",y,string[y]);
    } */

    return string;
}

char **AlocaMatriz(int m, int n)
{
    char **M;
    int i;
    char aux[1000];
    M = (char **)malloc(sizeof(char *) * m);
    if (M == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    for (i = 0; i < m; i++)
    {
        M[i] = (char *)malloc(sizeof(char) * n);
        if (M[i] == NULL)
        {
            printf("Memoria insuficiente.\n");
            exit(1);
        }
    }

    puts("saiu");
    return M;
}