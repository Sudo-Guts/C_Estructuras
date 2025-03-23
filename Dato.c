#include "library/Dato.h"

int main(){
    MyData Datito;
    Datito.tipo = FLOAT;
    printf("Ingresa dato:");
    ScanfDato( &Datito );
    PrintfDato( Datito );

    return 0;
}