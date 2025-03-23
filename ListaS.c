#include "library/ListS.h"

void Cargar_ListaS( ListaS *Lista ){
	Dato info; short tam;
	FILE *ListaSBin = fopen( "ListaS.bin" , "rb" );
	if( ListaSBin != NULL ){
		fread( &tam , sizeof( short ) , 1 , ListaSBin );
		for(  ; tam > 0 ; tam-- ){
			fread( &info , sizeof( Dato ) , 1 , ListaSBin );
			InsertEndS( Lista , info );
		}
	}
    fclose( ListaSBin );
}

void Guardar_ListaS( ListaS *Lista ){
	Dato info;
    FILE *ListaSBin = fopen( "ListaS.bin" , "wb" );
	if( ListaSBin != NULL ){
		fwrite( &(Lista->size) , sizeof( short ) , 1 , ListaSBin );
		while( !EmptyS( *Lista ) ){
            info = RemoveInS( Lista );
            fwrite( &info , sizeof( Dato ) , 1 , ListaSBin );
        }
	}
    fclose( ListaSBin );
}

short MENU(){
	short opcion = 0;
    do{
        printf("\n");
        printf("X--------------------------------------------------[ MENU ]--------------------------------------------------X\n");
        printf("|{ 00 }>                                        GUARDAR Y SALIR                                       <{ 00 }|\n");
        printf("|{ 01 }>                                         CARGAR LISTA                                         <{ 01 }|\n");
        printf("|{ 02 }>                                       CREAR NUEVA LISTA                                      <{ 02 }|\n");
        printf("|{ 03 }>                                 INSERTAR AL INICIO DE LA LISTA                               <{ 03 }|\n");
        printf("|{ 04 }>                                 INSERTAR AL FINAL DE LA LISTA                                <{ 04 }|\n");
        printf("|{ 05 }>                                 INSERTAR EN MEDIO DE LA LISTA                                <{ 05 }|\n");
        printf("|{ 06 }>                                         MOSTRAR LISTA                                        <{ 06 }|\n");
        printf("|{ 07 }>                                 ELIMINAR AL INICIO DE LA LISTA                               <{ 07 }|\n");
        printf("|{ 08 }>                                 ELIMINAR AL FINAL DE LA LISTA                                <{ 08 }|\n");
        printf("|{ 09 }>                                 ELIMINAR EN MEDIO DE LA LISTA                                <{ 09 }|\n");
        printf("|{ 10 }>                                          MERGE SHORT                                         <{ 10 }|\n");
        printf( "\n%cIngresa la opcion deseada:\n" , 201 );
        printf( "%c> " , 200 );
    }while( scanf( "%hd" , &opcion ) == EOF );
    printf("\nX---------------------------------------------------[ %hd ]---------------------------------------------------X\n", opcion );
	return opcion;
}

int main(){
    ListaS MAIN;
    Dato dato;
    StartS( &MAIN );
    short opcion , pos;

    do{
		opcion = MENU();
		switch(opcion){
            case 0:
                printf("\n[> Guardando <]\n");
				
                Guardar_ListaS( &MAIN );
				
                printf("\n[><]\n");
            break;

            case 1:
                printf("\n[> Cargar Lista <]\n");

                if( !EmptyS( MAIN ) ) printf("\nAviso: La lista actual se elimino\n");
                KillS( &MAIN );
				Cargar_ListaS( &MAIN );
                PrintListS( MAIN );
				
                printf("\n[><]\n");
            break;

            case 2:
                printf("\n[> Crear Nueva Lista <]\n");
                
                printf("\nAviso: La lista actual se elimino\n");
                KillS( &MAIN );

				printf("\n[><]\n");
            break;

            case 3:
                printf("\n[> Insertar Al Inicio <]\n");

                do{
                    printf( "\n%cIngresa un dato (int):\n" , 201 );
                    printf( "%c> " , 200 );
                }while ( scanf( "%d", &dato ) == EOF );
				InsertInS( &MAIN , dato );
                PrintListS( MAIN );

				printf("\n[><]\n");
            break;

            case 4:
                printf("\n[> Insertar Al Final <]\n");

				do{
                    printf( "\n%cIngresa un dato (int):\n" , 201 );
                    printf( "%c> " , 200 );
                }while ( scanf( "%d", &dato ) == EOF );
				InsertEndS( &MAIN , dato );
                PrintListS( MAIN );

				printf("\n[><]\n");
            break;

            case 5:
                printf("\n[> Insertar Al Final <]\n");
                printf("\n|-------------->Insertar En Medio<--------------|\n");

                PrintListS( MAIN );
                do{
                    printf( "\n%c||\n" , 201 );
                    printf( "%c[0-%hd]->Insertar\n" , 204 , MAIN.size + 1 );
                    printf( "%c> " , 200 );
                }while( scanf( "%hd" , &pos ) == EOF );
                do{
                    printf( "\n%cIngresa un dato (int):\n" , 201 );
                    printf( "%c> " , 200 );
                }while( scanf( "%d" , &dato ) == EOF );
				InsertHalfS( &MAIN , dato , pos );
                PrintListS( MAIN );

				 printf("\n[><]\n");
            break;

            case 6:
                printf("\n[> Mostrar Lista <]\n");
				
                PrintListS( MAIN );
				
                printf("\n[><]\n");
            break;

            case 7:
                printf("\n[> Eliminar Al Inicio <]\n");
				
                printf( "\nEl dato {%d} fue elimiado\n" , RemoveInS( &MAIN ) );
                PrintListS( MAIN );
				
                printf("\n[><]\n");
            break;

            case 8:
                printf("\n[> Eliminar Al Final <]\n");

                printf( "\nEl dato {%d} fue elimiado\n" , RemoveEndS( &MAIN ) );
                PrintListS( MAIN );
				
                printf("\n[><]\n");
            break;

            case 9:
                printf("\n[> Eliminar En Medio <]\n");

                PrintListS( MAIN );
                do{
                    printf( "\n%c||\n" , 201 );
                    printf( "%c[1-%hd]->Eliminar\n" , 204 , MAIN.size );
                    printf( "%c> " , 200 );
                }while( scanf( "%hd" , &pos ) == EOF );
				printf( "\nEl dato {%d} fue elimiado\n" , RemoveHalfS( &MAIN , pos ) );
                PrintListS( MAIN );

				printf("\n[><]\n");
            break;

            case 10:
                printf("\n[> Merge Short <]\n");
                
				Merge_ShortS( &MAIN );
                PrintListS( MAIN );
				
                printf("\n[><]\n");
            break;

            default:
                printf("\n|-------------------------------------------------->ERROR<--------------------------------------------------|\n");
				printf("\n                                              Opcion no valida '_'                                           \n");
				printf("\n|-----------------------------------------------------><----------------------------------------------------|\n");
            break;
        }

    }while( opcion != 0 );

    return 0;
}