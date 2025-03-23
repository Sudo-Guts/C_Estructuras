/*
{ Lista Simple de Listas Simples }
*/

#include "ListS.h"
#include <string.h>

typedef char DatoOut; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: Si cambias el dato debes modificar 
|   algunas cositas ;) .
*/

short i = 0; // La mejor variable xD

typedef struct NodoOutsideSimple{
	struct NodoOutsideSimple *next;
	ListaS lista;
	DatoOut info[10];
}NodoOutS;

typedef struct ListaOutsideSimple{
	NodoOutS *in;
	NodoOutS *end;
	short size;
}ListaOutS;

void StartOutS( ListaOutS *lista );
short EmptyOutS( ListaOutS lista );
short SearchOutS( ListaOutS lista , DatoOut Val[] );

NodoOutS *FindOutS( ListaOutS lista , short Pos );
NodoOutS *CreaNodoOutS( DatoOut Data[] );

void InsertOutsideInS( ListaOutS *lista , DatoOut Data[] );
void InsertOutsideEndS( ListaOutS *lista , DatoOut Data[] );
void InsertOutsideHalfS( ListaOutS *lista , DatoOut Data[] , short Pos );

void PrintListOutS( ListaOutS lista );
void PrintLListS( ListaOutS lista );

DatoOut RemoveOutsideInS( ListaOutS *lista );
DatoOut RemoveOutsideEndS( ListaOutS *lista );
DatoOut RemoveOutsideHalfS( ListaOutS *lista , short Pos );

void DivideOutS( ListaOutS *Lista , ListaOutS *Left , ListaOutS *Right );
void MergeOutS( ListaOutS *Lista , ListaOutS *Left , ListaOutS *Right );
void Merge_SortOutS( ListaOutS *lista );

void KillOutS( ListaOutS *lista );

void StartOutS( ListaOutS *lista ){
    lista->in = NULL;
	lista->end = NULL;
	lista->size = 0;
}

short EmptyOutS( ListaOutS lista ){
    return ( ( lista.size == 0 ) || ( ( lista.in == NULL ) && ( lista.end == NULL ) ) ) ? 1 : 0;
}

short SearchOutS( ListaOutS lista , DatoOut Val[] ){
    short pos;
	for( pos = 1 ; ( pos < lista.size ) && ( strcmp( (lista.in)->info , Val ) ) ; ++pos , lista.in = (lista.in)->next );
	return ( !strcmp( (lista.in)->info , Val ) ) ? pos : 0;
}

NodoOutS *FindOutS( ListaOutS lista , short Pos ){
	NodoOutS *NodO = lista.in;
	if( ( Pos < 1 ) || ( Pos > lista.size ) || ( EmptyOutS( lista ) ) ) NodO = NULL;
	else for( i = 1 ; i < Pos ; i++ ) NodO = NodO->next;
	return NodO;
}

NodoOutS *CreaNodoOutS( DatoOut Data[] ){
	NodoOutS *NodO;
	NodO = (NodoOutS*)malloc(sizeof(NodoOutS));
	if( NodO == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		strcpy( NodO->info , Data );
		NodO->next = NULL;
		StartS( &(NodO->lista) );
	}
	return NodO;
}

void InsertOutsideInS( ListaOutS *lista , DatoOut Data[] ){
	NodoOutS *NodO = CreaNodoOutS( Data );
	if( NodO != NULL ){
		if( EmptyOutS( *lista ) ){
			lista->in = NodO;
			lista->end = NodO;
			lista->size = 1;
		}else{
			NodO->next = lista->in;
			lista->in = NodO;
			++(lista->size);	
		}
	}
}

void InsertOutsideEndS( ListaOutS *lista , DatoOut Data[] ){
	NodoOutS *NodO = CreaNodoOutS( Data );
	if( NodO != NULL ){
		if( EmptyOutS( *lista ) ){
			lista->in = NodO;
			lista->end = NodO;
			lista->size = 1;
		}else{
			(lista->end)->next = NodO;
			lista->end = NodO;
			++(lista->size);
		}
	}
}

void InsertOutsideHalfS( ListaOutS *lista , DatoOut Data[] , short Pos ){
	if( EmptyOutS(*lista) )
		InsertOutsideInS( lista , Data );
	else if( Pos < 0 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 0 )
		InsertOutsideInS( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertOutsideEndS( lista , Data );
	else{
        NodoOutS *NodO = CreaNodoOutS( Data );
        if( NodO != NULL ){
			NodoOutS *back = lista->in;
        	for( i = 1 ; i < Pos ; i++ ) back = back->next;
       		NodO->next = back->next;
	     	back->next = NodO;
        	++(lista->size);
        }
	}	
}

void PrintListOutS( ListaOutS lista ){
	if( EmptyOutS( lista ) ) printf("\nLista vacia\n");
	else{
		printf( "\n{ " );
		for( ; lista.in != NULL ; lista.in = (lista.in)->next )
			printf( "[%s]%s" , (lista.in)->info , ( (lista.in)->next == NULL ) ? "-||" : "->" );
		printf( " (%hd) }\n" , lista.size );
    }
}

void PrintLListS( ListaOutS lista ){
	if( EmptyOutS( lista ) ) printf("\nLista vacia\n");
	else{
		NodoOutS *PrintOut = lista.in;
		NodoS *PrintIn = NULL;
		printf( "\n" );
		for( ; PrintOut != NULL ; PrintOut = PrintOut->next ){
			PrintIn = (PrintOut->lista.in);
			printf( "[%s]->" , PrintOut->info );
			for( ; PrintIn != NULL ; PrintIn = PrintIn->next )
				printf( "[%d]%s" , PrintIn->info , ( PrintIn->next == NULL ) ? "-||" : "->" );
			printf( " (%hd) \n" , PrintOut->lista.size );
			printf( "\t%s\n" , ( PrintOut->next == NULL ) ? "=" : "|" );
		}
		printf( "\t(%hd)\n" , lista.size );
	}
}

DatoOut RemoveOutsideInS( ListaOutS *lista ){
	DatoOut valor = 0;
	NodoOutS *kill = lista->in;
	if( EmptyOutS( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = *((lista->in)->info);
		if(lista->size == 1) StartOutS( lista );
		else{ 
			lista->in = (lista->in)->next;
			--(lista->size);
		}
		KillS( &(kill->lista) );
		free( kill );
	}
	return valor;
}

DatoOut RemoveOutsideEndS( ListaOutS *lista ){
	DatoOut valor = 0;
	NodoOutS *kill = lista->in;
	if( EmptyOutS( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = *((lista->end)->info);
		if( lista->size == 1 ) StartOutS( lista );
		else{
			for( i = 1 ; i < lista->size - 1 ; i++ ) kill = kill->next;
			lista->end = kill;
			(lista->end)->next = NULL;
			kill = kill->next;
			--(lista->size);
		}
		KillS( &(kill->lista) );
		free( kill );
	}
	return valor;
}

DatoOut RemoveOutsideHalfS( ListaOutS *lista , short Pos ){
	DatoOut valor = 0;
	if( EmptyOutS( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		RemoveOutsideInS( lista );
	else if( Pos == lista->size )
		RemoveOutsideEndS( lista );
	else{
		NodoOutS *kill , *back = lista->in;
		for( i = 1 ; i < Pos - 1 ; i++ ) back = back->next;
		kill = back->next;
		back->next = kill->next;
		valor = *(kill->info);
		KillS( &(kill->lista) );
		free( kill );
		--(lista->size);
	}
	return valor;
}

void DivideOutS( ListaOutS *Lista , ListaOutS *Left , ListaOutS *Right ){
    NodoOutS *half = NULL; short med;
	med = (Lista->size)/2;
	Left->in = Lista->in;
	Right->end =  Lista->end;
	Left->size = med;
	Right->size = Lista->size - med;
	half = Lista->in;
	for( i = 1 ; i < med ; i++ ) half = half->next;
	Left->end = half;
	Right->in = half->next;
	(Left->end)->next = NULL;
	StartOutS( Lista );
}

void MergeOutS( ListaOutS *Lista , ListaOutS *Left , ListaOutS *Right ){
    NodoOutS *aux = NULL;
	
	while ( !EmptyOutS( *Left ) && !EmptyOutS( *Right ) ){

		if( (Left->in)->info > (Right->in)->info ){

			if( EmptyOutS( *Lista ) ){
				Lista->in = Right->in;
				Lista->end = Right->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Right->in;
				Lista->end = Right->in;
				++(Lista->size);
				aux = aux->next;
			}
			Right->in = (Right->in)->next;
			--(Right->size);

		}else if( (Left->in)->info < (Right->in)->info ){

			if ( EmptyOutS( *Lista ) ){
				Lista->in = Left->in;
				Lista->end = Left->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Left->in;
				Lista->end = Left->in;
				++(Lista->size);
				aux = aux->next; 
			}
			Left->in = (Left->in)->next; 
			--(Left->size);

		}else{
		
			if( EmptyOutS( *Lista ) ){
				Lista->in = Right->in;
				Lista->end = Right->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Right->in;
				Lista->end = Right->in;
				++(Lista->size);
				aux = aux->next;
			}
			Right->in = (Right->in)->next;
			--(Right->size);

		}

	}

	if( !EmptyOutS( *Left ) ){
		(Lista->end)->next = Left->in;
		Lista->end = Left->end;
		Lista->size += Left->size;
	}

	if( !EmptyOutS( *Right ) ){
		(Lista->end)->next = Right->in;
		Lista->end = Right->end;
		Lista->size += Right->size;
	}

}

void Merge_SortOutS( ListaOutS *lista ){
	if( lista->size > 1 ){
		ListaOutS Left , Right;
		StartOutS( &Left ); StartOutS( &Right );
		DivideOutS( lista ,  &Left , &Right );
		Merge_SortOutS( &Left );
		Merge_SortOutS( &Right );
		MergeOutS( lista , &Left , &Right );
	}
}

void KillOutS( ListaOutS *lista ){
	for( ; lista->end != NULL ; lista->in = lista->end ){
		lista->end = (lista->in)->next;
		//printf( "Se elimino: %s\n" , (lista->in)->info );
		KillS( &((lista->in)->lista) );
		free( lista->in );
	}
	StartOutS( lista );
}
/*
void KillOutS( ListaOutS *lista ){ // Recursivo
	if( !EmptyOutS( *lista ) ){
		//printf( "Se elimino: %s\n" , (lista->in)->info );
		if( lista->in == lista->end ){
			KillS( &((lista->in)->lista) );
			free( lista->in );
			StartOutS( lista );
		}else{
			NodoOutS *kill = lista->in;
			lista->in = (lista->in)->next;
			KillS( &(kill->lista) );
    		free( kill );
      		KillOutS( lista );
		}
	}
}
*/