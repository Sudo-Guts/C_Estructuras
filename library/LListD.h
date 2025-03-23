/*
{ Lista Doble de Listas Dobles }
*/

#include "ListD.h"
#include <string.h>

typedef char DatoOut; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: Si cambias el dato debes modificar 
|   algunas cositas ;) .
*/

short i = 0; // La mejor variable xD

typedef struct NodoOutsideDoble{
	struct NodoOutsideDoble *next;
	struct NodoOutsideDoble *past;
	ListaD lista;
	DatoOut info[10];
}NodoOutD;

typedef struct ListaOutsideDoble{
	NodoOutD *in;
	NodoOutD *end;
	short size;
}ListaOutD;

void StartOutD( ListaOutD *lista );
short EmptyOutD( ListaOutD lista );
short SearchOutD( ListaOutD lista , DatoOut Val[] );

NodoOutD *FindOutD( ListaOutD lista , short Pos );
NodoOutD *CreaNodoOutD( DatoOut Data[] );

void InsertOutsideInD( ListaOutD *lista , DatoOut Data[] );
void InsertOutsideEndD( ListaOutD *lista , DatoOut Data[] );
void InsertOutsideHalfD( ListaOutD *lista , DatoOut Data[] , short Pos );

void PrintListOutD( ListaOutD lista );
void PrintLListD( ListaOutD lista );

DatoOut RemoveOutsideInS( ListaOutD *lista );
DatoOut RemoveOutsideEndS( ListaOutD *lista );
DatoOut RemoveOutsideHalfS( ListaOutD *lista , short Pos );

void DivideOutD( ListaOutD *Lista , ListaOutD *Left , ListaOutD *Right );
void MergeOutD( ListaOutD *Lista , ListaOutD *Left , ListaOutD *Right );
void Merge_SortOutD( ListaOutD *lista );

void KillOutD( ListaOutD *lista );

void StartOutD( ListaOutD *lista ){
    lista->in = NULL;
	lista->end = NULL;
	lista->size = 0;
}

short EmptyOutD( ListaOutD lista ){
    return ( ( lista.size == 0 ) || ( ( lista.in == NULL ) && ( lista.end == NULL ) ) ) ? 1 : 0;
}

short SearchOutD( ListaOutD lista , DatoOut Val[] ){
    short pos;
	for( pos = 1 ; ( pos < lista.size ) && ( strcmp( (lista.in)->info , Val ) ) ; ++pos , lista.in = (lista.in)->next );
	return ( !strcmp( (lista.in)->info , Val ) ) ? pos : 0;
}

NodoOutD *FindOutD( ListaOutD lista , short Pos ){
	NodoOutD *NodO = lista.in;
	if( ( Pos < 1 ) || ( Pos > lista.size ) || ( EmptyOutD( lista ) ) ) NodO = NULL;
	else for( i = 1 ; i < Pos ; i++ ) NodO = NodO->next;
	return NodO;
}

NodoOutD *CreaNodoOutD( DatoOut Data[] ){
	NodoOutD *NodO;
	NodO = (NodoOutD*)malloc(sizeof(NodoOutD));
	if( NodO == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		strcpy( NodO->info , Data );
		NodO->next = NULL;
		StartD( &(NodO->lista) );
	}
	return NodO;
}

void InsertOutsideInD( ListaOutD *lista , DatoOut Data[] ){
	NodoOutD *NodO = CreaNodoOutD( Data );
	if( NodO != NULL ){
		if( EmptyOutD( *lista ) ){
			lista->end = NodO;
			lista->in = NodO;
			lista->size = 1;
		}else{
			NodO->next = lista->in;
			(lista->in)->past = NodO;
	    	lista->in = NodO;
			++(lista->size);	
		}
	}
}

void InsertOutsideEndD( ListaOutD *lista , DatoOut Data[] ){
	NodoOutD *NodO = CreaNodoOutD( Data );
	if( NodO != NULL ){
		if( EmptyOutD( *lista ) ){
			lista->in = NodO;
			lista->end = NodO;
			lista->size = 1;
		}else{
			NodO->past = lista->end;
			(lista->end)->next = NodO;
			lista->end = NodO;
			++(lista->size);
		}
	}
}

void InsertOutsideHalfD( ListaOutD *lista , DatoOut Data[] , short Pos ){
	if( EmptyOutD(*lista) )
		InsertOutsideInD( lista , Data );
	else if( Pos < 0 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 0 )
		InsertOutsideInD( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertOutsideEndD( lista , Data );
	else{
        NodoOutD *NodO = CreaNodoOutD( Data );
        if( NodO != NULL ){
			NodoOutD *insert , *back = lista->in;
        	for( i = 1 ; i < Pos ; i++ ) back = back->next;
        	insert = back->next;
       		NodO->next = insert;
       		insert->past = NodO;
       		NodO->past = back;
        	back->next = NodO;
        	++(lista->size);
        }
	}	
}

void PrintListOutD( ListaOutD lista ){
	if( EmptyOutD( lista ) ) printf("\nLista vacia\n");
	else{
		printf( "\n{ %s" , "||-" );
		for( ; lista.in != NULL ; lista.in = (lista.in)->next )
			printf( "[%d]%s" , (lista.in)->info , ( (lista.in)->next == NULL ) ? "-||" : "<=>" );
		printf( " (%hd) }\n" , lista.size );
    }
}

void PrintLListD( ListaOutD lista ){
	if( EmptyOutD( lista ) ) printf("\nLista vacia\n");
	else{
		NodoOutD *PrintOut = lista.in;
		NodoD *PrintIn = NULL;
		printf( "\n" );
		for( ; PrintOut != NULL ; PrintOut = PrintOut->next ){
			PrintIn = (PrintOut->lista.in);
			printf( "[%s]->" , PrintOut->info );
			for( ; PrintIn != NULL ; PrintIn = PrintIn->next ) 
				printf( "[%d]-%c" , PrintIn->info , ( PrintIn->next == NULL ) ? "║" : ">" );
			printf( " (%hd) \n" , PrintOut->lista.size );
			printf( "\t%c\n" , ( PrintOut->next == NULL ) ? "╩" : "│" );
		}
		printf( "\t(%hd)\n" , lista.size );
	}
}

DatoOut RemoveOutsideInD( ListaOutD *lista ){
	DatoOut valor = 0;
	NodoOutD *kill = lista->in;
	if( EmptyOutD( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = *((lista->in)->info);
		if(lista->size == 1) StartOutD( lista );
		else{
			lista->in = (lista->in)->next;
			(lista->in)->past = NULL;
			--(lista->size);
		}
		KillD( &(kill->lista) );
		free( kill );
	}
	return valor;
}

DatoOut RemoveOutsideEndD( ListaOutD *lista ){
	DatoOut valor = 0;
	NodoOutD *kill = lista->in;
	if( EmptyOutD( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = *((lista->end)->info);
		if( lista->size == 1 ) StartOutD( lista );
		else{
			lista->end = (lista->end)->past;
			(lista->end)->next = NULL;
			--(lista->size);
		}
		KillD( &(kill->lista) );
		free( kill );
	}
	return valor;
}

DatoOut RemoveOutsideHalfD( ListaOutD *lista , short Pos ){
	DatoOut valor = 0;
	if( EmptyOutD( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size )
		printf("Error: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		RemoveOutsideInD( lista );
	else if( Pos == lista->size )
		RemoveOutsideEndD( lista );
	else{
		NodoOutD *kill , *back = lista->in;
		for( i = 1 ; i < Pos - 1 ; i++ ) back = back->next;
		kill = back->next;
        back->next = kill->next;
        (kill->next)->past = back;
		valor = *(kill->info);
		KillD( &(kill->lista) );
		free( kill );
		--(lista->size);
	}
	return valor;
}

void DivideOutD( ListaOutD *Lista , ListaOutD *Left , ListaOutD *Right ){
	NodoOutD *half = NULL; short med;
	med = (Lista->size)/2;
	Left->in = Lista->in;
	Right->end =  Lista->end;
	Left->size = med;
	Right->size = Lista->size - med;
	half = Lista->in;
	for( i = 1 ; i < med ; i++ ) half = half->next;
	Left->end = half;
	Right->in = half->next;
	(Left->in)->past = NULL; (Left->end)->next = NULL;
	(Right->in)->past = NULL; (Right->end)->next = NULL;
	StartOutD( Lista );
}

void MergeOutD( ListaOutD *Lista , ListaOutD *Left , ListaOutD *Right ){
	NodoOutD *aux = NULL;
	
	while ( !EmptyOutD( *Left ) && !EmptyOutD( *Right ) ){

		if( (Left->in)->info > (Right->in)->info ){
		
			if( EmptyOutD( *Lista ) ){
				Lista->in = Right->in;
				Lista->end = Right->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Right->in;
				(Right->in)->past = aux;
				Lista->end = Right->in;
				++(Lista->size);
				aux = aux->next;
			}
			Right->in = (Right->in)->next;
			--(Right->size);
		
		}else if( (Left->in)->info < (Right->in)->info ){

			if ( EmptyOutD( *Lista ) ){
				Lista->in = Left->in;
				Lista->end = Left->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Left->in;
				(Left->in)->past = aux;
				Lista->end = Left->in;
				++(Lista->size);
				aux = aux->next;
			}
			Left->in = (Left->in)->next;
			--(Left->size);

		}else{
		
			if( EmptyOutD( *Lista ) ){
				Lista->in = Right->in;
				Lista->end = Right->in;
				Lista->size = 1;
				aux = Lista->in;
			}else{
				aux->next = Right->in;
				(Right->in)->past = aux;
				Lista->end = Right->in;
				++(Lista->size);
				aux = aux->next;
			}
			Right->in = (Right->in)->next;
			--(Right->size);

		}

		if( !EmptyOutD( *Left ) ){
			(Lista->end)->next = Left->in;
			(Left->in)->past = Lista->end;
			Lista->end = Left->end;
			Lista->size += Left->size;
		}

		if( !EmptyOutD( *Right ) ){
			(Lista->end)->next = Right->in;
			(Right->in)->past = Lista->end;
			Lista->end = Right->end;
			Lista->size += Right->size;
		}

	}

}

void Merge_SortOutD( ListaOutD *lista ){
	if( lista->size > 1 ){
		ListaOutD Left , Right;
		StartOutD( &Left ); StartOutD( &Right );
		DivideOutD( lista ,  &Left , &Right );
		Merge_SortOutD( &Left );
		Merge_SortOutD( &Right );
		MergeOutD( lista , &Left , &Right );
	}
}

void KillOutD( ListaOutD *lista ){
	for( ; lista->end != NULL ; lista->in = lista->end ){
		lista->end = (lista->in)->next;
		//printf( "Se elimino: %s\n" , (lista->in)->info );
		KillD( &((lista->in)->lista) );
		free( lista->in );
	}
	StartOutD( lista );
}
/*
void KillOutD( ListaOutD *lista ){ // Recursivo
	if( !EmptyOutD( *lista ) ){
		//printf( "Se elimino: %s\n" , (lista->in)->info );
		if( lista->in == lista->end ){
			KillD( &((lista->in)->lista) );
			free( lista->in );
			StartOutD( lista );
		}else{
			NodoOutD *kill = lista->in;
			lista->in = (lista->in)->next;
			KillD( &(kill->lista) );
    		free( kill );
      		KillOutD( lista );
		}
	}
}
*/