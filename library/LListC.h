#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoInsideC{
	int info;
	struct NodoInsideC *next;
}NodoInC;

typedef struct InsideC{
	NodoInC *head;
	short size;
}ListaInC;

typedef struct NodoOutsideC{
	char grupo[10];
	struct NodoOutsideC *next;
	ListaInC Lista;
}NodoOutC;

typedef struct OutsideC{
	NodoOutC *head;
	short size;
}ListaOutC;

void startOutC( ListaOutC *lista );
void startInC( ListaInC *lista );

short vaciaOutC( ListaOutC lista );
short vaciaInC( ListaInC lista );

short searchOutC( ListaOutC lista, char val[] );
short searchInC( ListaInC lista, int val );

NodoOutC *creaNodoOutC( char data[] );
NodoInC *creaNodoIntC( int data );

void InsertaNextOutC( ListaOutC *lista, char data[] );
void InsertaNextInC( ListaInC *lista, int data );

void InsertaPastOutC( ListaOutC *lista, char data[] );
void InsertaPastInC( ListaInC *lista, int data );

void InsertaHalfOutC( ListaOutC *lista, char data[], short pos );
void InsertaHalfInC( ListaInC *lista, int data, short pos );

void PrintListOutC( ListaOutC lista );
void PrintListInC( ListaInC lista );

void EliminaNextOutC( ListaOutC *lista );
int EliminaNextInC( ListaInC *lista );

void EliminaPastOutC( ListaOutC *lista );
int EliminaPastInC( ListaInC *lista );

void EliminaHalfOutC( ListaOutC *lista, short pos );
int EliminaHalfInC( ListaInC *lista, short pos );

void KILLOUTC( ListaOutC *lista );
void KILLINC( ListaInC *lista );

void startOutC( ListaOutC *lista ){
	lista->head = NULL;
	lista->size = 0;
}

void startInC( ListaInC *lista ){
	lista->head = NULL;
	lista->size = 0;
}

short vaciaOutC( ListaOutC lista ){
	return ( lista.head == NULL )? 1:0;
}

short vaciaInC( ListaInC lista ){
	return ( lista.head == NULL )? 1:0;
}

short searchOutC( ListaOutC lista, char val[] ){
	short pos;
	for( pos = 0 ; strcmp((lista.head)->grupo,val) && pos < lista.size ; ++pos, lista.head = (lista.head)->next );
	return ( !strcmp((lista.head)->grupo,val) )? pos:-1;
}

short searchInC( ListaInC lista, int val ){
	short pos;
	for( pos = 0 ; (lista.head)->info != val && pos < lista.size ; ++pos, lista.head = (lista.head)->next );
	return ( (lista.head)->info == val )? pos:-1;
}

NodoOutC *creaNodoOutC( char data[] ){
	NodoOutC *NodO;
	NodO = (NodoOutC*)malloc(sizeof(NodoOutC));
	if( NodO == NULL ) printf("Error: Espacio de memoria llena\n");
	else{
		strcpy(NodO->grupo,data);
		NodO->next = NULL;
		startInC( &(NodO)->Lista );
	}
	return NodO;
}

NodoInC *creaNodoInC( int data ){
	NodoInC *NodI;
	NodI = (NodoInC*)malloc(sizeof(NodoInC));
	if( NodI == NULL ) printf("Error: Espacio de memoria llena\n");
	else{
		NodI->info = data;
		NodI->next = NULL;
	}
	return NodI;
}

void InsertaNextOutC( ListaOutC *lista, char data[] ){
	NodoOutC *NodO = creaNodoOutC(data);
	if( NodO != NULL ){
		if( vaciaOutC(*lista) ){
			NodO->next = NodO;
			lista->head = NodO;
			lista->size = 1;
		}else{
			NodO->next = (lista->head)->next;
			(lista->head)->next = NodO;
			++(lista->size);
		}
	}
}

void InsertaNextInC( ListaInC *lista, int data ){
	NodoInC *NodI = creaNodoInC(data);
	if( NodI != NULL ){
		if( vaciaInC(*lista) ){
			NodI->next = NodI;
			lista->head = NodI;
			lista->size = 1;
		}else{
			NodI->next = (lista->head)->next;
			(lista->head)->next = NodI;
			++(lista->size);
		}
	}
}

void InsertaPastOutC( ListaOutC *lista, char data[] ){
	NodoOutC *NodO = creaNodoOutC(data);
	if( NodO != NULL ){
		if( vaciaOutC(*lista) ){
			NodO->next = NodO;
			lista->head = NodO;
			lista->size = 1;
		}else{
			NodoOutC *back = lista->head;
			while( back->next != lista->head ) back = back->next;
			NodO->next = lista->head;
			back->next = NodO;
	  		++(lista->size);
		}
	}
}

void InsertaPastInC( ListaInC *lista, int data ){
	NodoC *nodo = creaNodoC(data);
	if( nodo != NULL ){
		if( vaciaC(*lista) ){
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

void InsertaHalfC( ListaC *lista, int data, short pos ){
	if( vaciaC(*lista) )
		InsertaNextC(lista,data);
	else if( pos <= 0 || pos > lista->size + 1 )
		printf("Error: Posicion incorrecta dentro de la lista\n");
	else if( pos == 1 )
		InsertaNextC(lista,data);
	else if( pos == lista->size + 1 )
		InsertaPastC(lista,data);
	else{
        NodoC *nodo = creaNodoC(data);
        if( nodo != NULL ){
			NodoC *back = lista->head, *insert; short i;
        	for( i = 0 ; i < pos - 1 ; i++ ) back = back->next;
        	insert = back->next;
       		nodo->next = insert;
        	back->next = nodo;
        	++(lista->size);	
        }
	}		
}

void PrintListC( ListaC lista ){
	if( vaciaC(lista) ) printf("Lista vacia\n");
	else{
		ListaC print = lista;
		do{
			if( print.head == lista.head ) printf(" ->{%d}->",(print.head)->info);
			else printf("[%d]->",(print.head)->info);
			print.head = (print.head)->next;
		}while( print.head != lista.head );
		printf(" (%hd)\n\n",lista.size);
    }
}

int EliminaNextC( ListaC *lista ){
	int valor = 0;
	NodoC *kill;
	if( vaciaC(*lista) )printf("Error: Lista vacia \n");
	else{
		kill = (lista->head)->next;
		valor = kill->info;
		(lista->head)->next = kill->next;
		free( kill );
		if(lista->size == 1) startC(lista);
		else --(lista->size);
	}
	return valor;
}

int EliminaPastC( ListaC *lista ){
	int valor = 0;
	NodoC *back,*kill;
	if( vaciaC(*lista) ) printf("Error: Lista vacia \n");
	else{
	    back = lista->head; short i;
		for( i = 0 ; i < lista->size - 2 ; i++ ) back = back->next;
		kill = back->next;
		valor = kill->info;
		back->next = lista->head;
		free( kill );
		if(lista->size == 1) startC(lista);
		else --(lista->size);
	}
	return valor;
}

int EliminaHalfC( ListaC *lista, short pos ){
    int valor = 0;
	if( vaciaC(*lista) ) 
		printf("Error: Lista vacia\n");
	else if( pos <= 0 || pos > lista->size )
		printf("Error: Posicion incorrecta dentro de la lista\n");
	else if( pos == 1 )
		valor = EliminaNextC(lista);
	else if( pos == lista->size )
		valor = EliminaPastC(lista);
	else{
		NodoC *back = lista->head, *kill; short i;
        for( i = 0 ; i < pos - 1 ; i++ ) back = back->next;
        kill = back->next;
        back->next = kill->next;
        free( kill );
        if(lista->size == 1) startC(lista);
		else --(lista->size);
	}
	return valor;
}

void KILLC( ListaC *lista ){
	ListaC kill;
	if( !vaciaC(*lista) ){
		kill.head = (lista->head)->next;
		if( kill.head == lista->head ){
			//printf("Se elimino: %d\n",(lista->head)->info);
			free(lista->head);
			startC(lista);
		}else{
			(lista->head)->next = (kill.head)->next;
			//printf("Se elimino: %d\n",(kill.head)->info);
			free(kill.head);
			KILLC(lista);
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

