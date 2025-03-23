/*
{ Pila en formato de una Lista }
*/

#include <stdio.h>
#include <stdlib.h>

typedef char Dato; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: En la funcion print debes de cambiar 
|   el tipo de dato que quieres imprimir :(.
*/

typedef struct nodoPila{
	struct nodoPila *next;
	Dato info;
}NodoPila;

typedef struct pila{
	NodoPila *in;
	NodoPila *end;
	short size;
	short tope;
}Stack;

short StartPila( Stack *Pila , short Size );
short EmptyPila( Stack Pila );
short FullPila( Stack Pila );
short SearchPila( Stack Pila , Dato Val );

NodoPila *CreaNodoPila( Dato Data );

void Push( Stack *Pila , Dato Data );
Dato Pop( Stack *Pila );

void PrintPila( Stack Pila );
void KillPila( Stack *Pila );

short StartPila( Stack *Pila , short Size ){
	if( Size <= 0 ) printf("\nError: Tamanio de la pila invalida\n");
	else{
		Pila->in = NULL;
		Pila->end = NULL;
		Pila->size = Size;
		Pila->tope = 0;
	}
	return ( Size > 0 ) ? 1 : 0;
}

short EmptyPila( Stack Pila ){
	return ( ( Pila.tope == 0 ) || ( ( Pila.in == NULL ) && ( Pila.end == NULL ) ) ) ? 1 : 0;
}

short FullPila( Stack Pila ){
	return ( Pila.tope >= Pila.size ) ? 1 : 0;
}

short SearchPila( Stack Pila , Dato Val ){
	short pos;
	for( pos = 1 ; ( pos < Pila.tope ) && ( (Pila.in)->info != Val ) ; ++pos , Pila.in = (Pila.in)->next );
	return ( (Pila.in)->info == Val ) ? pos : 0;
}

NodoPila *CreaNodoPila( Dato Data ){
	NodoPila *Nodo;
	Nodo = (NodoPila*)malloc(sizeof(NodoPila));
	if( Nodo == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		Nodo->info = Data;
		Nodo->next = NULL;
	}
	return Nodo;
}

void Push( Stack *Pila , Dato Data ){
	NodoPila *Nodo = CreaNodoPila( Data );
	if( Nodo != NULL ){
		if( EmptyPila( *Pila ) ){
			Pila->in = Nodo;
			Pila->end = Nodo;
			Pila->tope = 1;
		}else{
			if( FullPila( *Pila ) ){
				printf("\nError: Pila llena\n");
				free( Nodo );
			}else{
				Nodo->next = Pila->in;
				Pila->in = Nodo;
				++(Pila->tope);
			}
		}
	}
}

Dato Pop( Stack *Pila ){
	Dato valor = 0;
	NodoPila *kill = Pila->in;
	if( EmptyPila( *Pila ) ) printf("\nError: Pila vacia\n");
	else{
		valor = kill->info;
		if( Pila->tope == 1 ) StartPila( Pila , Pila->size );
		else{
			Pila->in = (Pila->in)->next;
			--(Pila->tope);
		}
		free( kill );
	}
	return valor;
}

void PrintPila( Stack Pila ){
	if( EmptyPila( Pila ) ) printf("\nPila Vacia\n");
	else{
		NodoPila *print = Pila.in;
		printf( "\n{ {%hd} " , Pila.size );
		for( ; print != NULL ; print = print->next ) printf( "[%c]" , print->info );
		printf( " (%hd) }\n" , Pila.tope );
	}
}

void KillPila( Stack *Pila ){
	for( ; Pila->end != NULL ; Pila->in = Pila->end ){
		Pila->end = (Pila->in)->next;
		//printf( "Se elimino: %d\n" , (Pila->in)->info );
		free( Pila->in );
	}
	StartPila( Pila , Pila->size );
}
/*
void KillPila( Stack *Pila ){ // Recusivo :o
	if( !EmptyPila( *Pila ) ){
		//printf( "Se elimino: %c\n" , (Pila->in)->info );
		if( Pila->in == Pila->end ){
			free( Pila->in );
			StartPila( Pila , Pila->size );
		}else{
			NodoPila *Kill = Pila->in;
			Pila->in = (Pila->in)->next;
			free( Kill );
			KillPila( Pila );
		}
	}
}
*/