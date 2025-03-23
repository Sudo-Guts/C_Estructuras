/*
{ Lista Simple }
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

typedef struct NodoSimple{
	struct NodoSimple *next;
	Dato info;
}NodoS;

typedef struct ListaSimple{
	NodoS *in;
	NodoS *end;
	short size;
}ListaS;

void StartS( ListaS *lista );
short EmptyS( ListaS lista );
short SearchS( ListaS lista , Dato Val );

NodoS *FindS( ListaS lista , short Pos );
NodoS *CreaNodoS( Dato Data );

void InsertInS( ListaS *lista , Dato Data );
void InsertEndS( ListaS *lista , Dato Data );
void InsertHalfS( ListaS *lista , Dato Data , short Pos );

void PrintListS( ListaS lista );

Dato RemoveInS( ListaS *lista );
Dato RemoveEndS( ListaS *lista );
Dato RemoveHalfS( ListaS *lista , short Pos );

void DivideS( ListaS *Lista , ListaS *Left , ListaS *Right );
void MergeS( ListaS *Lista , ListaS *Left , ListaS *Right );
void Merge_SortS( ListaS *lista );

void KillS( ListaS *lista );

void StartS( ListaS *lista ){
	lista->in = NULL;
	lista->end = NULL;
	lista->size = 0; 
}

short EmptyS( ListaS lista ){
	return ( ( lista.size == 0 ) || ( ( lista.in == NULL ) && ( lista.end == NULL ) ) ) ? 1 : 0;
}

short SearchS( ListaS lista , Dato Val ){
	short pos;
	for( pos = 1 ; ( pos < lista.size ) && ( (lista.in)->info != Val ) ; ++pos , lista.in = (lista.in)->next );
	return ( (lista.in)->info == Val ) ? pos : 0;
}

NodoS *FindS( ListaS lista , short Pos ){
	NodoS *nodo = lista.in;
	if( ( Pos < 1 ) || ( Pos > lista.size ) || ( EmptyS( lista ) ) ) nodo = NULL;
	else for( i = 1 ; i < Pos ; i++ ) nodo = nodo->next;
	return nodo;
}
/*
NodoS *FindS( ListaS lista , short Pos ){
	NodoS *nodo = lista.in;
	if( ( Pos >= 1 ) && ( Pos <= lista.size ) && ( !EmptyD( lista ) ) ) 
		for( i = 1 ; i < Pos ; i++ ) nodo = nodo->next;
	else nodo = NULL;
	return nodo;
}
*/
NodoS *CreaNodoS( Dato Data ){
	NodoS *nodo;
	nodo = (NodoS*)malloc(sizeof(NodoS));
	if( nodo == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		nodo->info = Data;
		nodo->next = NULL;
	} 
	return nodo;
}

void InsertInS( ListaS *lista , Dato Data ){
	NodoS *nodo = CreaNodoS( Data );
	if( nodo != NULL ){
		if( EmptyS( *lista ) ){
			lista->in = nodo;
			lista->end = nodo;
			lista->size = 1;
		}else{
			nodo->next = lista->in;
			lista->in = nodo;
			++(lista->size);	
		}
	}
}

void InsertEndS( ListaS *lista , Dato Data ){
	NodoS *nodo = CreaNodoS( Data );
	if( nodo != NULL ){
		if( EmptyS( *lista ) ){
			lista->in = nodo;
			lista->end = nodo;
			lista->size = 1;
		}else{
			(lista->end)->next = nodo;
			lista->end = nodo;
			++(lista->size);	
		}
	}
}

void InsertHalfS( ListaS *lista , Dato Data , short Pos ){
	if( EmptyS( *lista ) )
		InsertInS( lista , Data );
	else if( Pos < 0 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 0 )
		InsertInS( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertEndS( lista , Data ); 
	else{
        NodoS *nodo = CreaNodoS( Data );
        if( nodo != NULL ){
			NodoS *back = lista->in;
        	for( i = 1 ; i < Pos ; i++ ) back = back->next;
       		nodo->next = back->next;
        	back->next = nodo;
        	++(lista->size);
        }
	}		
}

void PrintListS( ListaS lista ){
	if( EmptyS( lista ) ) printf("\nLista vacia\n");
	else{
		printf( "\n{ " );
		for( ; lista.in != NULL ; lista.in = (lista.in)->next )
			printf( "[%d]%s" , (lista.in)->info , ( (lista.in)->next == NULL ) ? "-||" : "->" );
		printf( " (%hd) }\n" , lista.size );
    }
}

Dato RemoveInS( ListaS *lista ){
	Dato valor = 0;
	NodoS *kill = lista->in;
	if( EmptyS( *lista ) )printf("\nError: Lista vacia \n");
	else{
		valor = (lista->in)->info;
		if( lista->size == 1 ) StartS( lista );
		else{
			lista->in = (lista->in)->next;
			--(lista->size);
		}
		free( kill );
	}
	return valor;
}

Dato RemoveEndS( ListaS *lista ){
	Dato valor = 0;
	NodoS *kill = lista->in;
	if( EmptyS( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = (lista->end)->info;
		if( lista->size == 1 ) StartS( lista );
		else{
			for( i = 1 ; i < lista->size - 1 ; i++ ) kill = kill->next;
			lista->end = kill;
			(lista->end)->next = NULL;
			kill = kill->next;
			--(lista->size);
		}
		free( kill );
	}
	return valor;
}

Dato RemoveHalfS( ListaS *lista , short Pos ){
    Dato valor = 0;
	if( EmptyS( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		valor = RemoveInS( lista );
	else if( Pos == lista->size )
		valor = RemoveEndS( lista );
	else{
		NodoS *kill , *back = lista->in;
        for( i = 1 ; i < Pos - 1 ; i++ ) back = back->next;
        kill = back->next;
        back->next = kill->next;
		valor = kill->info;
        free( kill );
		--(lista->size);
	}
	return valor;
}

void DivideS( ListaS *Lista , ListaS *Left , ListaS *Right ){
	NodoS *half = NULL; short med;
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
	StartS( Lista );
}

void MergeS( ListaS *Lista , ListaS *Left , ListaS *Right ){
	NodoS *aux = NULL;
	
	while ( !EmptyS( *Left ) && !EmptyS( *Right ) ){

		if( (Left->in)->info > (Right->in)->info ){

			if( EmptyS( *Lista ) ){
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

			if ( EmptyS( *Lista ) ){
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
		
			if( EmptyS( *Lista ) ){
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

	if( !EmptyS( *Left ) ){
		(Lista->end)->next = Left->in;
		Lista->end = Left->end;
		Lista->size += Left->size;
	}

	if( !EmptyS( *Right ) ){
		(Lista->end)->next = Right->in;
		Lista->end = Right->end;
		Lista->size += Right->size;
	}

}

void Merge_SortS( ListaS *lista ){
	if( lista->size > 1 ){
		ListaS Left , Right;
		StartS( &Left ); StartS( &Right );
		DivideS( lista ,  &Left , &Right );
		Merge_SortS( &Left ); 
		Merge_SortS( &Right );
		MergeS( lista , &Left , &Right ); 
	}
}

void KillS( ListaS *lista ){
	for( ; lista->end != NULL ; lista->in = lista->end ){
		lista->end = (lista->in)->next;
		//printf( "Se elimino: %d\n" , (lista->in)->info );
		free( lista->in );
	}
	StartS( lista );
}
/*
void KillS( ListaS *lista ){ // Recusivo :o
	if( !EmptyS( *lista ) ){
		printf( "Se elimino: %d\n" , (lista->in)->info );
		if( lista->in == lista->end ){
			free( lista->in );
			StartS( lista );
		}else{
			NodoS *kill = lista->in;
			lista->in = (lista->in)->next;
    		free( kill );
    		KillS( lista );
		}
	}
}
*/