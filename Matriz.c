#include <stdio.h>
#include <stdlib.h>

int** CrearMatriz( int F , int C ){
    int i = 0 ;
    int **M = (int**) malloc(F*sizeof(int));
    for( i = 0 ; i < F ; i++ ) 
    *(M+i) = (int*) malloc(C*sizeof(int));
    return M;
}

void CrearMatriz2( int ***M ,  int F , int C ){
    int i = 0 ;
    *M = (int**) malloc(F*sizeof(int));
    for( i = 0 ; i < F ; i++ ) 
    *(M[i]) = (int*) malloc(C*sizeof(int));
}

void Free( int **M , int F ){
    for( int i = 0 ; i < F ; i++ ) free( *(M+i) );
    free( M );
}

void PedirDatos( int **M , int F , int C ){
    int i,j,dato = 0;
    for( i = 0 ; i < F ; i++ ){
        printf("\n|-Para la fila [%d]:\n", i );
        for( j = 0 ; j < C ; j++ ){
            printf("|-El dato de la fila[%d] y columna[%d]:\n",i,j);
            printf("|-> "); scanf("%d",&dato);
            *(*(M+i)+j) = dato;
        }
    }
}

void ImprimirMatriz( int **M, int F , int C ){
    printf("\n");
    for( int i = 0 ; i < F ; i++ ){
        for( int j = 0 ; j < C ; j++ ){
            printf( "  %d  ", *(*(M+i)+j) );
        }
        printf("\n\n");
    }
}

int main(){
    int **MatrizMain = NULL;
    int F,C;
    printf("\n|-Ingresa el tamanio de la fila:\n");
    printf("|-> "); scanf("%d",&F);

    printf("|-Ingresa el tamanio de la columna:\n");
    printf("|-> "); scanf("%d",&C);

    MatrizMain = CrearMatriz( F , C );
    //CrearMatriz2( &MatrizMain , F , C );
    PedirDatos( MatrizMain , F , C );
    ImprimirMatriz( MatrizMain , F ,C );

    printf("Recorrido:\n");
    int *P = *MatrizMain;
    for( int i = 0 ; i < F*C ; i++ ) printf("Dato[%d] = %d\n" , i , *(P+i));

    Free( MatrizMain , F );
    printf("\nFIN\n");
    return 0;
}