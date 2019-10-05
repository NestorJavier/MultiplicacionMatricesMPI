#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "mpi.h"

int getNumeroRandom();
int* generaMatriz(int fil, int col);
void llenaMatriz(int* matriz, int fil, int col);
void imprime(int* matriz, int fil, int col);
int validaArgumentos(int argc, char *argv[], int idProc);

int main(int argc, char *argv[]){
    srand(time(NULL));
    setlocale(LC_ALL,"es_MX");
    int idProc, numProc, nDatos, nDatosU, filA, colA, filB, colB;   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if(!validaArgumentos(argc, argv, idProc)){
        MPI_Finalize();
        return 0;
    }
    filA = atoi(argv[1]);
    colA = atoi(argv[2]);
    filB = atoi(argv[3]);
    colB = atoi(argv[4]);
    int* A = generaMatriz(filA, colA);
    int *B = generaMatriz(filB, colB); 
    int *C = generaMatriz(filA, colB); //Matriz resultante
    if(idProc == 0){
        llenaMatriz(A, filA, colA);
        llenaMatriz(B, filB, colB);
        imprime(A, filA, colA);
        imprime(B, filB, colB);
    }
    MPI_Bcast(A, filA * colA, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, filB * colB, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(C, filA * colB, MPI_INT, 0, MPI_COMM_WORLD); //Matriz resultante
    MPI_Finalize();
    return 0;
}

int validaArgumentos(int argc, char *argv[], int idProc){
    if(argc < 5){
        if(!idProc){
            printf("Te faltan argumentos\n");
        }
        return 0;
    }
    if(!atoi(argv[1]) || atoi(argv[1]) < 0){
        if(!idProc){
            printf("La cantidad de filas de la matriz A no es válida\n");
        }
        return 0;
    }
    if(!atoi(argv[2]) || atoi(argv[2]) < 0){
        if(!idProc){
            printf("La cantidad de columnas de la matriz A no es válida\n");
        }
        return 0;
    }
    if(!atoi(argv[3]) || atoi(argv[3]) < 0){
        if(!idProc){
            printf("La cantidad de filas de la matriz B no es válida\n");
        }
        return 0;
    }
    if(!atoi(argv[4]) || atoi(argv[4]) < 0){
        if(!idProc){
            printf("La cantidad de columnas de la matriz B no es válida\n");
        }
        return 0;
    }
    if(!multiplicacionValida(atoi(argv[1]), atoi(argv[4]))){     
        if(!idProc){
            printf("La cantidad de filas de la matriz A no es igual a la cantidad de columnas de la fila B\n");
        }
        return 0;
    }
    return 1;
}

int getNumeroRandom(int limInf, int limSup){
    
    return rand() % limSup + limInf;
}

int* generaMatriz(int fil, int col){
    int* matriz = (int*)malloc(fil * col * sizeof(int));
    return matriz;
}

void llenaMatriz(int* matriz, int fil, int col){
    int i, j;
    for(i = 0; i < fil * col; i++){
        int num = getNumeroRandom(1, 100);
        matriz[i] = num;
    }
}

void imprime(int* matriz, int fil, int col){
    int i;
	for(i = 0; i < fil * col; i++)
	{
        printf("%d ", matriz[i]);
		if((i + 1) % col == 0){
            printf("\n");
        }
	}
    printf("\n");
}

int multiplicacionValida(int filA, int colB){
    if(filA == colB){
        return 1;
    }
    return 0;
}

int filaXColumna(int* fil, int* col, int datos){
    int i, resultado;
    resultado = 0;
    for(i = 0; i < datos; i++){
        resultado += *(fil + i) * *(col + i);
    }
    return resultado;
}
