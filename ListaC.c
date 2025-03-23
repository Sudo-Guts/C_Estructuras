#include <stdio.h>
#include <stdlib.h>
#include "library/ListC.h"

void Cargar_ListaC( ListaC *Lista ){
	Dato info; short tam;
	FILE *ListaCBin = fopen( "ListaS.bin" , "rb" );
	if( ListaCBin == NULL ) printf( "Aviso: Archivo no encontrado, se a creado uno.\n" ); 
    else {
		fread( &tam , sizeof( short ) , 1 , ListaCBin );
		for(  ; tam > 0 ; tam-- ){
			fread( &info , sizeof( Dato ) , 1 , ListaCBin );
			InsertNextC( Lista , info );
		}
	}
    fclose( ListaCBin );
}

void Guardar_ListaC( ListaC *Lista ){
	Dato info;
    FILE *ListaSBin = fopen( "ListaS.bin" , "wb" );
	if( ListaSBin == NULL ) printf( "Error: Archivo no encontrado." );
    else{
		fwrite( &(Lista->size) , sizeof( short ) , 1 , ListaSBin );
		while( !EmptyS( *Lista ) ){
            info = RemoveNextC( Lista );
            fwrite( &info , sizeof( Dato ) , 1 , ListaSBin );
        }
	}
    fclose( ListaSBin );
}
