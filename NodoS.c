#include "library/ListS.h"

int main(){
    ListaS MAIN; StartS( &MAIN );
    NodoS *NODI = NULL;
    short pos = 0;

    InsertInS( &MAIN , 1 );
    InsertEndS( &MAIN , 4 );
    InsertHalfS( &MAIN , 3 , 1 );
    InsertHalfS( &MAIN , 5 , 2 );
    InsertHalfS( &MAIN , 6 , 3 );
    InsertInS( &MAIN , 8 );
    InsertEndS( &MAIN , 12 );
    InsertHalfS( &MAIN , 9 , 2 );
    InsertHalfS( &MAIN , 55 , 4 );
    InsertHalfS( &MAIN , 13 , 6 );
    InsertHalfS( &MAIN , 13 , 6 );
    
    Merge_SortS( &MAIN );

    PrintListS( MAIN );

    pos = SearchS( MAIN , 55 );

    NODI = FindS( MAIN , pos );

    if( NODI == NULL )printf( "\nNo encontramos nodo :C\n" );
    else{
        printf( "\nValor del nodo: %d\n" , NODI->info );
        NODI->info = 11;
    }

    PrintListS( MAIN );

    KillS( &MAIN );

    PrintListS( MAIN );

    return 0;
}