/*
{ Mi dato personalizado }
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    STRING,
    FLOAT,
    BYTE,
}Type;

typedef struct Data{
    Type tipo;
    union {
        char str[64];
        float num;
        char byte;
    };
}MyData;

void PrintfDato( MyData Dato );
short ScanfDato( MyData *Dato );

void PrintfDato( MyData Dato ){
    switch ( Dato.tipo ){
        case STRING: printf( "%s" , Dato.str );
        break;
        case FLOAT: printf( "%.f" , Dato.num );
        break;
        case BYTE: printf( "%c" , Dato.byte );
        break;
    }
}

short ScanfDato( MyData *Dato ){
    short r = 0;
    switch ( Dato->tipo ){
        case STRING: 
            gets( Dato->str );
            r = 1;
        break;
        case FLOAT: 
            r = scanf( "%f" , &(Dato->num) );
            if( r == 0 ) Dato->num = 0;
        break;
        case BYTE:
            r = scanf( "%c" , &(Dato->byte) );
            if( r == 0 ) Dato->byte = ' ';
        break;
    }
    fflush(stdin);
    return r;
}