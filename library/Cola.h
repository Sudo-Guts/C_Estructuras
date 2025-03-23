/*
{ Cola en formato de una Lista }
*/

#include "Dato.h"

typedef struct nodoCola{
	struct nodoCola *next;
	MyData info;
}NodoCola;

typedef struct cola{
	NodoCola *in;
	NodoCola *end;
	short size;
	short tope;
}Queue;

short StartCola( Queue *Cola , short Size );
short EmptyCola( Queue Cola );
short FullCola( Queue Cola );
short SearchCola( Queue Cola , MyData Val );

NodoCola *CreaNodoCola( MyData Data );

void Enqueue( Queue *Cola , MyData Data ); //Encolar
MyData Dequeue( Queue *Cola ); //Desencolar

void PrintCola( Queue Cola );
void KillCola( Queue *cola );

short StartCola( Queue *Cola , short Size ){
	if( Size <= 0 ) printf("\nError: tamanio de la cola invalida\n");
	else{
		Cola->in = NULL;
		Cola->end = NULL;
		Cola->size = Size;
		Cola->tope = 0;
	}
	return ( Size > 0 ) ? 1 : 0;
}

short EmptyCola( Queue Cola ){
	return ( ( Cola.tope == 0 ) || ( ( Cola.in == NULL ) && ( Cola.end == NULL ) ) ) ? 1 : 0;
}

short FullCola( Queue Cola ){
	return ( Cola.tope >= Cola.size ) ? 1 : 0;
}

short SearchCola( Queue Cola , MyData Val ){
	short pos;
	switch ( Val.tipo ){
		case STRING:
			for( pos = 1 ; ( pos < Cola.tope ) && ( strcmp( (Cola.in)->info.str , Val.str ) ) ; ++pos , Cola.in = (Cola.in)->next );
			pos = ( !strcmp( (Cola.in)->info.str , Val.str ) ) ? pos : 0; 
		break;
		case FLOAT:
			for( pos = 1 ; ( pos < Cola.tope ) && ( (Cola.in)->info.num != Val.num ) ; ++pos , Cola.in = (Cola.in)->next );
			pos = ( (Cola.in)->info.num == Val.num ) ? pos : 0;
		break;
		case BYTE:
			for( pos = 1 ; ( pos < Cola.tope ) && ( (Cola.in)->info.byte != Val.byte ) ; ++pos , Cola.in = (Cola.in)->next );
			pos = ( (Cola.in)->info.byte == Val.byte ) ? pos : 0;
		break;
	}
	return pos;
}

NodoCola *CreaNodoCola( MyData Data ){
	NodoCola *Nodo;
	Nodo = (NodoCola*)malloc(sizeof(NodoCola));
	if( Nodo == NULL ) printf("\nError: Espacio de memoria llena\n");
	else{
		switch ( Data.tipo ){
			case STRING: strcpy( Nodo->info.str , Data.str );
			break;
			case FLOAT: Nodo->info.num = Data.num;
			break;
			case BYTE: Nodo->info.byte = Data.byte;
			break;
		}
		Nodo->next = NULL;
	}
	return Nodo;
}

void Enqueue( Queue *Cola , MyData Data ){
	NodoCola *Nodo = CreaNodoCola( Data );
	if( Nodo != NULL ){
		if( EmptyCola( *Cola ) ){
			Cola->in = Nodo;
			Cola->end = Nodo;
			Cola->tope = 1;
		}else{
			if( FullCola( *Cola ) ){
				printf("\nError: Cola llena\n");
				free( Nodo );
			}else{
				(Cola->end)->next = Nodo;
				Cola->end = Nodo;
				++(Cola->tope);
			}
		}
	}
}

MyData Dequeue( Queue *Cola ){
	MyData valor;
	NodoCola *kill = Cola->in;
	if( EmptyCola( *Cola ) ) printf("\nERROR: Cola vacia\n");
	else{
		valor = kill->info;
		if( Cola->tope == 1 ) StartCola( Cola , Cola->size );
		else{
			Cola->in = (Cola->in)->next;
			--(Cola->tope);
		}
		free( kill );
	}
	return valor;
}

void PrintCola( Queue Cola ){
	if( EmptyCola( Cola ) ) printf("\nCola Vacia\n");
	else{
		NodoCola *print = Cola.in;
		printf( "\n{ {%hd} " , Cola.size );
		for( ; print != NULL ; print = print->next ){
			printf( "[" );
			PrintfDato( print->info );
			printf( "]" );
		}
		printf( " (%hd) }\n" , Cola.tope );
	}
}

void KillCola( Queue *Cola ){
	for( ; Cola->end != NULL ; Cola->in = Cola->end ){
		Cola->end = (Cola->in)->next;
		//printf( "Se elimino: ");
		//PrintfDato( (Cola->in)->info );
		//printf( "\n" );
		free( Cola->in );
	}
	StartCola( Cola , Cola->size );
}
/*
void KillCola( Queue *Cola ){ // Recusivo :o
	if( !EmptyCola( *Cola ) ){
		//printf( "Se elimino: ");
		//PrintfDato( (Cola->in)->info );
		//printf( "\n" );
		if( Cola->in == Cola->end ){
			free( Cola->in );
			StartCola( Cola , Cola->size );
		}else{
			NodoCola *kill = Cola->in;
			Cola->in = (Cola->in)->next;
			free( kill );
			KillCola( Cola );
		}
	}
}
*/