/*
{ Lista Doble }
*/

#include <stdio.h>
#include <stdlib.h>

typedef int Dato; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes elegir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: Si cambias el dato debes modificar 
|   algunas cositas ;) .
*/

short i = 0; // La mejor variable xD

typedef struct NodoDoble{
	struct NodoDoble *next;
	struct NodoDoble *past;
	Dato info;
}NodoD;

typedef struct ListaDoble{
	NodoD *in;
	NodoD *end;
	short size;
}ListaD;

void StartD( ListaD *lista );
short EmptyD( ListaD lista );
short SearchD( ListaD lista , Dato Val );

NodoD *FindD( ListaD lista , short Pos );
NodoD *CreaNodoD( Dato Data );

void InsertInD( ListaD *lista , Dato Data );
void InsertEndD( ListaD *lista , Dato Data );
void InsertHalfD( ListaD *lista , Dato Data , short Pos );

void PrintListD( ListaD lista );

Dato RemoveInD( ListaD *lista );
Dato RemoveEndD( ListaD *lista );
Dato RemoveHalfD( ListaD *lista , short Pos );

void DivideD( ListaD *Lista , ListaD *Left , ListaD *Right );
void MergeD( ListaD *Lista , ListaD *Left , ListaD *Right );
void Merge_SortD( ListaD *lista );

void KillD( ListaD *lista );

void StartD( ListaD *lista ){
	lista->in = NULL;
	lista->end = NULL;
	lista->size = 0; 
}

short EmptyD( ListaD lista ){
  	return ( ( lista.size == 0 ) || ( ( lista.in == NULL ) && ( lista.end == NULL ) ) ) ?  1 : 0;
}

short SearchD( ListaD lista , Dato Val ){
	short pos;
	for( pos = 1 ; ( pos < lista.size ) && ( (lista.in)->info != Val ) ; ++pos, lista.in = (lista.in)->next );
	return ( (lista.in)->info == Val ) ? pos : 0;
}

NodoD *FindD( ListaD lista , short Pos ){
	NodoD *nodo = lista.in;
	if( ( Pos < 1 ) || ( Pos > lista.size ) || ( EmptyD( lista ) ) ) nodo = NULL;
	else for( i = 1 ; i < Pos ; i++ ) nodo = nodo->next;
	return nodo;
}

NodoD *CreaNodoD( Dato Data ){
	NodoD *nodo;
	nodo = (NodoD*)malloc(sizeof(NodoD));
	if( nodo == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		nodo->info = Data;
		nodo->past = NULL;
		nodo->next = NULL;
	}
	return nodo;
}

void InsertInD( ListaD *lista , Dato Data ){
	NodoD *nodo = CreaNodoD( Data );
	if( nodo != NULL ){
		if( EmptyD( *lista ) ){
			lista->end = nodo;
			lista->in = nodo;
			lista->size = 1;
		}else{
			nodo->next = lista->in;
			(lista->in)->past = nodo;
	    	lista->in = nodo;
			++(lista->size);	
		}
	}
}

void InsertEndD( ListaD *lista , Dato Data ){
	NodoD *nodo = CreaNodoD( Data );
	if( nodo != NULL ){
		if( EmptyD( *lista ) ){
			lista->end = nodo;
			lista->in = nodo;
			lista->size = 1;
		}else{
			nodo->past = lista->end;
			(lista->end)->next = nodo;
			lista->end = nodo;
			++(lista->size);
		}
	}
}

void InsertHalfD( ListaD *lista , Dato Data , short Pos ){
	if( EmptyD( *lista ) )
		InsertInD( lista , Data );
	else if( Pos < 0 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 0 )
		InsertInD( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertEndD( lista , Data );
	else{
        NodoD *nodo = CreaNodoD( Data );
        if( nodo != NULL ){
			NodoD *insert , *back = lista->in;
        	for( i = 1 ; i < Pos ; i++ ) back = back->next;
        	insert = back->next;
       		nodo->next = insert;
       		insert->past = nodo;
       		nodo->past = back;
        	back->next = nodo;
        	++(lista->size);
        }
	}
}

void PrintListD( ListaD lista ){
	if( EmptyD( lista ) ) printf("\nLista vacia\n");
	else{
		printf( "\n{ %s" , "||-" );
		for( ; lista.in != NULL ; lista.in = (lista.in)->next )
			printf( "[%d]%s" , (lista.in)->info , ( (lista.in)->next == NULL ) ? "-||" : "<=>" );
		printf( " (%hd) }\n" , lista.size );
    }
}

Dato RemoveInD( ListaD *lista ){
	Dato valor = 0;
	NodoD *kill = lista->in;
	if( EmptyD( *lista ) ) printf("\nERROR: Lista vacia\n");
	else{
		valor = kill->info;
		if( lista->size == 1 ) StartD( lista );
		else{
			lista->in = (lista->in)->next;
			(lista->in)->past = NULL;
			--(lista->size);
		}
		free( kill );
	}
    return valor;
}

Dato RemoveEndD( ListaD *lista ){
	Dato valor = 0;
	NodoD *kill = lista->end;
	if( EmptyD( *lista ) ) printf("\nERROR: Lista vacia\n");
	else{
		valor = kill->info;
		if(lista->size == 1) StartD( lista );
		else{
			lista->end = (lista->end)->past;
			(lista->end)->next = NULL;
			--(lista->size);
		}
		free( kill );
	}
    return valor;
}

Dato RemoveHalfD( ListaD *lista , short Pos ){
	Dato valor = 0;
	if( EmptyD( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		valor = RemoveInD( lista );
	else if( Pos == lista->size )
		valor = RemoveEndD( lista );
	else{
		NodoD  *kill , *back = lista->in;
        for( i = 1 ; i < Pos - 1 ; i++ ) back = back->next;
        kill = back->next;
        back->next = kill->next;
        (kill->next)->past = back;
		valor = kill->info;
        free( kill );
		--(lista->size);
	}
	return valor;
}

void DivideD( ListaD *Lista , ListaD *Left , ListaD *Right ){
	NodoD *half = NULL; short med;
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
	StartD( Lista );
}

void MergeD( ListaD *Lista , ListaD *Left , ListaD *Right ){
	NodoD *aux = NULL;
	
	while ( !EmptyD( *Left ) && !EmptyD( *Right ) ){

		if( (Left->in)->info > (Right->in)->info ){
		
			if( EmptyD( *Lista ) ){
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

			if ( EmptyD( *Lista ) ){
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
		
			if( EmptyD( *Lista ) ){
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

		if( !EmptyD( *Left ) ){
			(Lista->end)->next = Left->in;
			(Left->in)->past = Lista->end;
			Lista->end = Left->end;
			Lista->size += Left->size;
		}

		if( !EmptyD( *Right ) ){
			(Lista->end)->next = Right->in;
			(Right->in)->past = Lista->end;
			Lista->end = Right->end;
			Lista->size += Right->size;
		}

	}

}

void Merge_SortD( ListaD *lista ){
	if( lista->size > 1 ){
		ListaD Left , Right;
		StartD( &Left ); StartD( &Right );
		DivideD( lista ,  &Left , &Right );
		Merge_SortD( &Left );
		Merge_SortD( &Right );
		MergeD( lista , &Left , &Right );
	}
}

void KillD( ListaD *lista ){
	for( ; lista->end != NULL ; lista->in = lista->end ){
		lista->end = (lista->in)->next;
		printf( "Se elimino: %d\n" , (lista->in)->info );
		free( lista->in );
	}
	StartD( lista );
}
/*
void KillD( ListaD *lista ){ // Recusivo :o
	if( !EmptyD( *lista ) ){
		printf( "Se elimino: %d\n" , (lista->in)->info );
		if( lista->in == lista->end ){
			free( lista->in );
			StartD( lista );
		}else{
			NodoD *kill = lista->in;
			lista->in = (lista->in)->next;
    		free( kill );
    		KillD( lista );
		}
	}
}
*/