/*
{ Lista Circular Doble }
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

typedef struct NodoCircularDoble{
	struct NodoCircularDoble *next;
	struct NodoCircularDoble *past;
	Dato info;	
}NodoCD;

typedef struct ListaCircularDoble{
	NodoCD *head;
	short size;
}ListaCD;

void StartCD( ListaCD *lista );
short EmptyCD( ListaCD lista );
short SearchCD( ListaCD lista , Dato Val );

NodoCD *FindCD( ListaCD lista , short Pos );
NodoCD *CreaNodoCD( Dato Data );

void InsertNextCD( ListaCD *lista , Dato Data );
void InsertPastCD( ListaCD *lista , Dato Data );
void InsertHalfCD( ListaCD *lista , Dato Data , short Pos );

void PrintListCD( ListaCD lista );

Dato RemoveNextCD( ListaCD *lista );
Dato RemovePastCD( ListaCD *lista );
Dato RemoveHalfCD( ListaCD *lista , short Pos );

void KillCD( ListaCD *next );

void StartCD( ListaCD *lista ){
	lista->head = NULL;
	lista->size = 0;
}

short EmptyCD( ListaCD lista ){
	return ( lista.head == NULL ) ? 1 : 0;
}

short SearchCD( ListaCD lista , Dato Val ){
	short pos;
	for( pos = 0 ; (lista.head)->info != Val && pos < lista.size ; ++pos, lista.head = (lista.head)->next );
	return ( (lista.head)->info == Val ) ? pos : -1;
}

NodoCD *FindCD( ListaCD lista , short Pos ){
	NodoCD *nodo = lista.head;
	if( ( !EmptyCD( lista ) ) && ( Pos <= lista.size && Pos >= 1 ) )
		for( i = 0 ; i < Pos ; i++ ) nodo = nodo->next;
	return nodo;
}

NodoCD *CreaNodoCD( Dato Data ){
	NodoCD *nodo;
	nodo = (NodoCD*)malloc(sizeof(NodoCD));
	if( nodo == NULL ) printf("Error: Espacio de memoria llena\n");
	else{
		nodo->info = Data;
		nodo->past = NULL;
		nodo->next = NULL;
	}
	return nodo;
}

void InsertNextCD( ListaCD *lista , Dato Data ){
	NodoCD *nodo = CreaNodoCD( Data );
	if( nodo != NULL ){
		if( EmptyCD( *lista ) ){
			lista->head = nodo;
			nodo->next = nodo;
			nodo->past = nodo;
			lista->size = 1;
		}else{
			nodo->next = (lista->head)->next;
			(lista->head)->next = nodo;
			(nodo->next)->past = nodo;
			nodo->past = lista->head;
			++(lista->size);
		}
	}
}

void InsertPastCD( ListaCD *lista , Dato Data ){
	NodoCD *nodo = CreaNodoCD( Data );
	if( nodo != NULL ){
		if( EmptyCD( *lista ) ){
			lista->head = nodo;
			nodo->next = nodo;
			nodo->past = nodo;
			lista->size = 1;
		}else{
			nodo->past = (lista->head)->past;
			nodo->next = lista->head;
			(nodo->past)->next = nodo;
			(lista->head)->past = nodo;
			++(lista->size);
		}
	}
}

void InsertHalfCD( ListaCD *lista , Dato Data , short Pos ){
	if( EmptyCD(*lista) )
		InsertNextCD( lista , Data );
	else if( Pos < 1 || Pos > lista->size + 1 )
		printf("Error: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		InsertNextCD( lista , Data );
	else if( Pos == lista->size + 1 )
		InsertPastCD( lista , Data );
	else{
        NodoCD *nodo = CreaNodoCD( Data );
        if( nodo != NULL ){
			NodoCD *insert , *back = lista->head;
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

void PrintListCD( ListaCD lista ){
	if( EmptyCD( lista ) ) printf("Lista vacia\n");
	else{
		ListaCD print = lista;
		printf( "\n" );
		do{
			if( print.head == lista.head ) printf( "s <->{%d}<->" , (print.head)->info );
			else printf( "[%d]<->" , (print.head)->info );
			print.head = (print.head)->next;
		}while( print.head != lista.head );
		printf( " (%hd)\n" , lista.size );
    }
}

Dato RemoveNextCD( ListaCD *lista ){
	Dato valor = 0;
	NodoCD *kill = (lista->head)->next;
	if( EmptyCD( *lista ) ) printf("\nError: Lista vacia\n");
	else{
		valor = kill->info;
		if( lista->size == 1 ) StartCD( lista );
		else{
			(lista->head)->next = kill->next;
			(kill->next)->past = lista->head;
			--(lista->size);
		}
		free( kill );
	}
    return valor;
}

Dato RemovePastCD( ListaCD *lista ){
	Dato valor = 0;
	NodoCD *kill = (lista->head)->past;
	if( EmptyCD( *lista ) ) printf("\nError: Lista vacia\n");
	else{
		valor = kill->info;
		if( lista->size == 1 ) StartCD( lista );
		else{
			(lista->head)->past = kill->past;
			(kill->past)->next = lista->head;
			--(lista->size);
		}
		free( kill );
	}
    return valor;
}

Dato RemoveHalfCD( ListaCD *lista , short Pos ){
	Dato valor = 0;
	if( EmptyCD( *lista ) ) 
		printf("\nError: Lista vacia\n");
	else if( Pos < 1 || Pos > lista->size + 1 )
		printf("\nError: Posicion incorrecta dentro de la lista\n");
	else if( Pos == 1 )
		valor = RemoveNextCD( lista );
	else if( Pos == lista->size + 1 )
		valor = RemovePastCD( lista );
	else{
		NodoCD *kill , *back = lista->head;
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

void KillCD( ListaCD *lista ){
	ListaCD kill;
	if( !EmptyCD( *lista ) ){
		kill.head = (lista->head)->next;
		//printf("Se elimino: %d\n",(lista->head)->info);
		if( kill.head == lista->head ){
			free( lista->head );
			StartCD( lista );
		}else{
			(lista->head)->next = (kill.head)->next;
			free( kill.head );
			KillCD( lista );
    	}
	}
}
