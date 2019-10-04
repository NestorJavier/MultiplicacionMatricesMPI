#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "mpi.h"

int getNumeroRandom();
int* generaMatriz(int fil, int col);
void llenaMatriz(int* matriz, int fil, int col);
void imprime(int* matriz, int fil, int col);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    setlocale(LC_ALL,"es_MX");
    if(argc < 5)
    {
        printf("Te faltan argumentos");
        return 0;
    }
    int filA, colA, filB, colB;
    filA = atoi(argv[1]);
    colA = atoi(argv[2]);
    filB = atoi(argv[3]);
    colB = atoi(argv[4]);
    int *A = generaMatriz(filA, colA);
    int *B = generaMatriz(filB, colB);
    int idProc, numProc, nDatos, nDatosU, nElementosMatResu;
	nDatos = nElementosMatResu/(NumProc - 1);
    nDatosU = nDatos + nElementosMatResu%(NumProc - 1);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if(idProc == 0)
    {
        multiplicacionValida(filA, colB);
        llenaMatriz(A, filA, colA);
        llenaMatriz(B, filB, colB);
        imprime(A, filA, colA);
        imprime(B, filB, colB);
        nElementosMatResu = filA*colB;
        
    }
    MPI_Finalize();
    return 0;
}



int getNumeroRandom(int limInf, int limSup)
{
    
    return rand() % limSup + limInf;
}

int* generaMatriz(int fil, int col)
{
    int* matriz = (int*)malloc(fil * col * sizeof(int));
    return matriz;
}

void llenaMatriz(int* matriz, int fil, int col)
{
    int i, j;
    for(i = 0; i < fil * col; i++){
        int num = getNumeroRandom(1, 100);
        matriz[i] = num;
    }
}

void imprime(int* matriz, int fil, int col)
{
    int i;
	for(i = 0; i < fil * col; i++)
	{
        printf("%d ", matriz[i]);
		if((i + 1) % col == 0)
        {
            printf("\n");
        }
	}
    printf("\n");
}

int multiplicacionValida(int filA, int colB)
{
    if(filA == colB){
        return 1;
    }
    return 0;
}
