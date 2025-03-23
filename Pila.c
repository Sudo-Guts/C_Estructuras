#include "library/Pila.h"

short Cargar_Pila( Stack *Pila ){
	Dato info; short size , tope , loaded = 0;
	FILE *PilaBin = fopen( "Pila.bin", "rb" );
	if( PilaBin != NULL ){
		fread( &loaded , sizeof( short ) , 1 , PilaBin );
		if( loaded ){
			fread( &size , sizeof( short ) , 1 , PilaBin );
			if( !StartPila( Pila , size ) ) loaded = 0;
			else{
				fread( &tope , sizeof( short ) , 1 , PilaBin );
				for(  ; tope > 0 ; tope-- ){
					fread( &info , sizeof( Dato ) , 1 , PilaBin );
					Push( Pila , info );
				}
				loaded = 1;
			}
		}
	}
	fclose( PilaBin );
	return loaded;
}

void Guardar_Pila( Stack *Pila , short loaded ){
	Dato info;
	FILE *PilaBin = fopen( "Cola.bin", "wb" );
	if( PilaBin != NULL ){
		fwrite( &loaded , sizeof( short ) , 1 , PilaBin );
		if( loaded ){
			fwrite( &(Pila->size) , sizeof( short ) , 1 , PilaBin );
			fwrite( &(Pila->tope) , sizeof( short ) , 1 , PilaBin );
			while( !EmptyPila( *Pila ) ){
				info = Pop( Pila );
				fwrite( &info , sizeof( Dato ) , 1 , PilaBin );
			}
		}
	}
	fclose( PilaBin );
}

short MENU(){
	short opcion;
	do{
		printf("\n");
		printf("X----------------------> MENU <-------------------X\n");
		printf("1>                 CREAR NUEVA PILA              <1\n");
		printf("2>                       PUSH                    <2\n");
		printf("3>                       PO0P                    <3\n");
		printf("4>                   MOSTRAR PILA                <4\n");
		printf("0>                 GUARDAR Y SALIR               <0\n");
		printf( "\n%cIngresa la opcion deseada:\n" , 201 );
		printf( "%c> " , 200 );
	}while( scanf( "%hd" , &opcion ) != 1 );            
    printf("\nX-----------------------><----------------------X\n");
	return opcion;
}

int main(){

    Stack MAIN;
	Dato dato;
	short tam, opcion, loaded;

	loaded = Cargar_Pila( &MAIN );

	if( loaded ){
		printf("\nLa Pila se cargo correctamente:\n");
		PrintPila( MAIN );
	}else{
		printf("\nLa Pila no se cargo correctamente:\n");
		printf("Se recomienda CREAR NUEVA PILA :) \n");
	}
	
	do{
		opcion = MENU();
		switch ( opcion ){
			case 0: 
				printf("\n|------------------>Guardando<------------------|\n");
				
				if( !loaded ) printf("\nAviso: No se ha creado una pila\n");
				Guardar_Pila( &MAIN , loaded );

				printf("\n|-----------------------><----------------------|\n");
			break;

			case 1:
				printf("\n|-------------->Crear Nueva Pila<---------------|\n");

				if( loaded ){
					printf("Aviso: La pila cargada se elimino\n");
					KillPila( &MAIN );
				}
				do{
					do{
						printf( "%cIngresa el tamanio de la pila: " , 201 );
						printf( "%c> " , 200 );
					}while( scanf( "%hd" , &tam ) != 1 ); 
   				}while( !StartPila( &MAIN , tam ) );
				loaded = 1;

				printf("\n|-----------------------><----------------------|\n");
			break;

			case 2:
				printf("\n|--------------------->PUSH<--------------------|\n");

				if( !loaded ) printf("\nError: No se ha creado una pila\n");
				else{
					do{
						printf( "\n%cIngresa un dato (char):\n" , 201 );
						printf( "%c> " , 200 );
					}while( scanf( "%c" , &dato ) != 1 );
					Push( &MAIN , dato );
				}

				printf("\n|-----------------------><----------------------|\n");
			break;

			case 3:
				printf("\n|--------------------->PO0P<--------------------|\n");

				if( !loaded ) printf("\nError: No se ha creado una pila\n");
				else printf( "\nEl dato %c fue eliminiado\n" , Pop( &MAIN ) );

				printf("\n|-----------------------><----------------------|\n");
			break;
			
			case 4: 
				printf("\n|---------------->Mostrar Pila<-----------------|\n");
				
				if( !loaded ) printf("\nError: No se ha creado una pila\n");
				else PrintPila( MAIN );
				
				printf("\n|-----------------------><----------------------|\n");
			break;

			default:
				printf("\n|--------------------->ERROR<-------------------|\n");
				printf("\n                Opcion no valida '_'             \n");
				printf("\n|-----------------------><----------------------|\n");
			break;
		}
	}while( opcion != 0 );

    return 0;
}