#include "library/Cola.h"

short Cargar_Cola( Queue *Cola ){
	MyData info; short size , tope , loaded = 0;
	FILE *ColaBin = fopen( "Cola.bin", "rb" );
	if( ColaBin != NULL ){
		fread( &loaded , sizeof( short ) , 1 , ColaBin );
		if( loaded ){
			fread( &size , sizeof( short ) , 1 , ColaBin );
			if( !StartCola( Cola , size ) ) loaded = 0;
			else{
				fread( &tope , sizeof( short ) , 1 , ColaBin );
				for(  ; tope > 0 ; tope-- ){
					fread( &info , sizeof( MyData ) , 1 , ColaBin );
					Enqueue( Cola , info );
				}
				loaded = 1;
			}
		}
	}
	fclose( ColaBin );
	return loaded;
}

void Guardar_Cola( Queue *Cola , short loaded ){
	MyData info;
	FILE *ColaBin = fopen( "Cola.bin", "wb" );
	if( ColaBin != NULL ){
		fwrite( &loaded , sizeof( short ) , 1 , ColaBin );
		if( loaded ){
			fwrite( &(Cola->size) , sizeof( short ) , 1 , ColaBin );
			fwrite( &(Cola->tope) , sizeof( short ) , 1 , ColaBin );
			while( !EmptyCola( *Cola ) ){
				info = Dequeue( Cola );
				fwrite( &info , sizeof( MyData ) , 1 , ColaBin );
			}
		}
	}
	fclose( ColaBin );
}

short MENU(){
	short opcion;
	do{
		printf("\n");
		printf("X---------------------> MENU <-------------------X\n");
		printf("1>                CREAR NUEVA COLA              <1\n");
		printf("2>                     ENCOLAR                  <2\n");
		printf("3>                    DESENCOLAR                <3\n");
		printf("4>                   MOSTRAR COLA               <4\n");
		printf("0>                  GUARDAR Y SALIR             <0\n");
		printf( "\n%cIngresa la opcion deseada:\n" , 201 );
		printf( "%c> " , 200 );
	}while( scanf( "%hd" , &opcion ) != 1 );             
    printf("\nX-----------------------><----------------------X\n");
	return opcion;
}

int main(){

    Queue MAIN;
	MyData dato;
	dato.tipo = FLOAT;
	short tam, opcion, loaded;

	loaded = Cargar_Cola( &MAIN );

	if( loaded ){
		printf("\nLa Cola se cargo correctamente:\n");
		PrintCola( MAIN );
	}else{
		printf("\nLa Cola no se cargo correctamente:\n");
		printf("Se recomienda CREAR NUEVA COLA :) \n");
	}
   
	do{
		opcion = MENU();
		switch ( opcion ){
			case 0: 
				printf("\n|------------------>Guardando<------------------|\n");

				if( !loaded ) printf("\nAviso: No se ha creado una cola\n");
				Guardar_Cola( &MAIN , loaded );
				
				printf("\n|-----------------------><----------------------|\n");
			break;
		
			case 1:
				printf("\n|-------------->Crear Nueva Cola<---------------|\n");
                
				if( loaded ){
					printf("Aviso: La cola cargada se elimino\n");
					KillCola( &MAIN );
				}
				do{
					printf( "%cIngresa el tamanio de la cola:\n" , 201 );
					printf( "%c> " , 200 );
					scanf( "%hd" , &tam ); 
   				}while( !StartCola( &MAIN , tam ) );
				loaded = 1;

				printf("\n|-----------------------><----------------------|\n");
			break;

			case 2:
				printf("\n|------------------->ENQUEUE<-------------------|\n");
				
				if( !loaded ) printf("\nError: No se ha creado una cola\n");
				else{
					do{
						printf( "\n%cIngresa un dato :\n" , 201 );
						printf( "%c> " , 200 );
						opcion = ScanfDato( &dato );
					}while( !opcion );
					Enqueue( &MAIN , dato );
				}
				
				printf("\n|-----------------------><----------------------|\n");
			break;

			case 3:
				printf("\n|------------------->DEQUEUE<-------------------|\n");
				
				if( !loaded ) printf("\nError: No se ha creado una cola\n");
				else{
					printf( "\nEl dato " );
					PrintfDato( Dequeue( &MAIN ) );
					printf( "fue eliminiado\n" );
				}
				printf("\n|-----------------------><----------------------|\n");
			break;
			
			case 4: 
				printf("|---------------->Mostrar Cola<-----------------|\n");
				
				if( !loaded ) printf("\nError: No se ha creado una cola\n");
				else PrintCola( MAIN );
				
				printf("|-----------------------><----------------------|\n");
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