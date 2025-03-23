/*
{ Lista Circular }
*/

#include <stdio.h>
#include <stdlib.h>

typedef int Dato; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: Si cambias el dato debes modificar 
|   algunas cositas ;) .
*/

short i = 0; // La mejor variable xD

typedef struct NodoCircular{
	struct NodoCircular *next;
	Dato info;
}NodoC;

typedef struct ListaCircular{
	NodoC *head;
	short size;
}ListaC;

void StartC( ListaC *lista );
short EmptyC( ListaC lista );
short SearchC( ListaC lista , Dato Val );

NodoC *FindC( ListaC lista , short Pos );
NodoC *CreaNodoC( Dato Data );

void InsertNextC( ListaC *lista , Dato Data );
void InsertPastC( ListaC *lista , Dato Data );
void InsertHalfC( ListaC *lista , Dato Data , short Pos );

void PrintListC( ListaC lista );

Dato RemoveNextC( ListaC *lista );
Dato RemovePastC( ListaC *lista );
Dato RemoveHalfC( ListaC *lista , short Pos );

void KillC( ListaC *lista );

void StartC( ListaC *lista ){
	lista->head = NULL;
	lista->size = 0;
}

short EmptyC( ListaC lista ){
	return ( ( lista.size == 0 ) || ( ( lista.size == 0 ) && ( lista.head == NULL ) ) ) ? 1 : 0;
}

short SearchC( ListaC lista, Dato Val ){
	short pos;
	for( pos = 0 ; ( pos < lista.size ) && ( (lista.head)->info != Val ) ; ++pos, lista.head = (lista.head)->next );
	return ( (lista.head)->info == Val ) ? pos : -1;
}

NodoC *FindC( ListaC lista , short Pos ){
	NodoC *nodo = lista.head;
	if( ( !EmptyC( lista ) ) && ( Pos <= lista.size && Pos >= 1 ) )
		for( i = 0 ; i < Pos ; i++ ) nodo = nodo->next;
	return nodo;
}

NodoC *CreaNodoC( Dato Data ){
	NodoC *nodo;
	nodo = (NodoC*)malloc(sizeof(NodoC));
	if( nodo == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		nodo->info = Data;
		nodo->next = NULL;
	}
	return nodo;
}

void InsertNextC( ListaC *lista , Dato Data ){
	NodoC *nodo = CreaNodoC( Data );
	if( nodo != NULL ){
		if( EmptyC( *lista ) ){
			nodo->next = nodo;
			lista->head = nodo;
			lista->size = 1;
		}else{
			nodo->next = (lista->head)->next;
			(lista->head)->next = nodo;
			++(lista->size);
		}
	}
}

void InsertPastC( ListaC *lista , Dato Data ){
	NodoC *nodo = CreaNodoC( Data );
	if( nodo != NULL ){
		if( EmptyC( *lista ) ){
			nodo->next = nodo;
			lista->head = nodo;
			lista->size = 1;
		}else{
			NodoC *back = lista->head;
			while( back->next != lista->head ) back = back->next;
			nodo->next = lista->head;
			back->next = nodo;
	  		++(lista->size);
		}
	}
}

void InsertHalfC( ListaC *lista , Dato Data , short Pos ){
	if( EmptyC( *lista ) )
		InsertNextC( lista , Data );
	else if( Pos < 1 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		InsertNextC( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertPastC( lista , Data );
	else{
        NodoC *nodo = CreaNodoC( Data );
        if( nodo != NULL ){
			NodoC *back = lista->head, *insert;
        	for( i = 1 ; i < Pos ; i++ ) back = back->next;
        	insert = back->next;
       		nodo->next = insert;
        	back->next = nodo;
        	++(lista->size);	
        }
	}		
}

void PrintListC( ListaC lista ){
	if( EmptyC( lista ) ) printf("\nLista vacia\n");
	else{
		NodoC *print = lista.head; 
		printf( "\n" );
		do{
			if( print == lista.head ) printf( " ->{%d}->" , print->info );
			else printf( "[%d]->" , print->info );
			print = print->next;
		}while(  print != lista.head );	
		printf( " (%hd)\n" , lista.size );
    }
}

Dato RemoveNextC( ListaC *lista ){
	Dato valor = 0;
	NodoC *kill = (lista->head)->next;
	if( EmptyC( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		valor = kill->info;
		if( lista->size == 1 ) StartC( lista );
		else{
			(lista->head)->next = kill->next;
			--(lista->size);
		}
		free( kill );
	}
	return valor;
}

Dato RemovePastC( ListaC *lista ){
	Dato valor = 0;
	NodoC *kill = lista->head;
	if( EmptyC( *lista ) ) printf("\nError: Lista vacia \n");
	else{
		if( lista->size == 1 ) StartC( lista );
		else{
			NodoC *back = kill;
			for( i = 1 ; i < lista->size - 1 ; i++ ) back = back->next;
			kill = back->next;
			back->next = lista->head;
			--(lista->size);
		}
		valor = kill->info;
		free( kill );
	}
	return valor;
}

Dato RemoveHalfC( ListaC *lista , short Pos ){
    Dato valor = 0;
	if( EmptyC( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		valor = RemoveNextC( lista );
	else if( Pos == lista->size + 1 )
		valor = RemovePastC( lista );
	else{
		NodoC  *kill , *back = lista->head;
        for( i = 1 ; i < Pos - 1 ; i++ ) back = back->next;
        kill = back->next;
        back->next = kill->next;
		valor = kill->info;
        free( kill );
		--(lista->size);
	}
	return valor;
}

void KillC( ListaC *lista ){
	NodoC *kill;
	while( (lista->head)->next != lista->head ){
		kill = (lista->head)->next;
		(lista->head)->next = kill->next;
		free( kill );
	}
	free( lista->head );
	StartC( lista );
}

void KillC( ListaC *lista ){
	ListaC kill;
	if( !EmptyC( *lista ) ){
		kill.head = (lista->head)->next;
		//printf("Se elimino: %d\n",(lista->head)->info);
		if( kill.head == lista->head ){
			free( lista->head );
			StartC( lista );
		}else{
			(lista->head)->next = (kill.head)->next;
			free( kill.head );
			KillC( lista );
    	}
	}
}
/*
void KILLC( ListaC *lista ){
	if( !vaciaC(*lista) ){
		NodoC *back; 
		while( (lista->head)->next != lista->head ){
			back = (lista->head)->next;
			(lista->head)->next = back->next;
			free(back);
		}
		free(lista->head);
		startC(lista);
	}
}*/

