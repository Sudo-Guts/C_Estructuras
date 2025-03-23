/*
{ RadixSort implementado a listas }
*/

// Mi codigo favorito <3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define D 10

typedef struct NodoInsideS{
	struct NodoInsideS *next;
    int num;
}NodoInS;

typedef struct InsideS{
	NodoInS *in;
	NodoInS *end;
	short size;
}ListaInS;

typedef struct NodoOutsideS{
    struct NodoOutsideS *next;
	ListaInS Lista;
	int dig;
}NodoOutS;

typedef struct OutsideS{
	NodoOutS *in;
	NodoOutS *end;
	short size;
}ListaOutS;

void startOutS( ListaOutS *lista );
void startInS( ListaInS *lista );

short vaciaOutS( ListaOutS lista );
short vaciaInS( ListaInS lista );

NodoOutS *creaNodoOutS( int data );
NodoInS *creaNodoInS( int data );

void InsertaInsideEndS( ListaInS *lista, int data );
int EliminaInsideInS( ListaInS *lista );

void PrintListOutS( ListaOutS lista );
void PrintListInS( ListaInS lista );
void PrintListLL( ListaOutS lista );

void Unificar( ListaOutS *Copy, ListaInS *Paste );
void RadixShort( ListaOutS *Arreglo, ListaInS *Lista );

int main(){
	
	ListaOutS Arreglo; 
	ListaInS Lista;
	
	int T,i,data;
	
	startOutS( &Arreglo );
	startInS( &Lista );
	
	printf("\n|Ingreesa la cantidad de elemtos que deseas agregar: \n");
	printf("|-> "); scanf( "%d" , &T );
	printf("\n");
	
	for( i = 0 ; i < T ; i++ ) {
		printf("|-[%d].Dato: \n" , i+1 );
		printf("|-> "); scanf( "%d", &data );
		InsertaInsideEndS( &Lista, data );
	}
	
	printf("\nArreglo antes:\n");
 	PrintListInS( Lista );
 	
 	RadixShort( &Arreglo , &Lista );
 	
	printf("\nArreglo Ordenado:\n");
 	PrintListInS( Lista );
 	printf("\n");	
	return 0;
}

void startOutS( ListaOutS *lista ){
	NodoOutS *NodO; int i;
	lista->in = NULL;
	lista->end = NULL;
	lista->size = 0;
	for( i = 0 ; i < D ; i++ ){
		NodO = creaNodoOutS(i);
		if( NodO != NULL ){
			if( vaciaOutS(*lista) ){
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
}

void startInS( ListaInS *lista ){
	lista->in = NULL;
	lista->end = NULL;
	lista->size = 0;
}

short vaciaOutS( ListaOutS lista ){
	return ( (lista.in == NULL) || (lista.end == NULL) )? 1:0;
}

short vaciaInS( ListaInS lista ){
	return ( (lista.in == NULL) || (lista.end == NULL) )? 1:0;
}

NodoOutS *creaNodoOutS( int data ){
	NodoOutS *NodO;
	NodO = (NodoOutS*)malloc(sizeof(NodoOutS));
	if( NodO == NULL ) printf("Error: Espacio de memoria llena\n");
	else{
		NodO->dig = data;
		NodO->next = NULL;
		startInS( &(NodO)->Lista );
	}
	return NodO;
}

NodoInS *creaNodoInS( int data ){
	NodoInS *NodI;
	NodI = (NodoInS*)malloc(sizeof(NodoInS));
	if( NodI == NULL ) printf("Error: Espacio de memoria llena\n");
	else{
		NodI->num = data;
		NodI->next = NULL;
	}
	return NodI;
} 

void InsertaInsideEndS( ListaInS *lista, int data ){
	NodoInS *NodI = creaNodoInS(data);
	if( NodI != NULL ){
		if( vaciaInS(*lista) ){
			lista->in = NodI;
			lista->end = NodI;
			lista->size = 1;
		}else{
			(lista->end)->next = NodI;
			lista->end = NodI;
			++(lista->size);
		}
	}
}

int EliminaInsideInS( ListaInS *lista ){
	int valor = 0;
	ListaInS kill = *lista;
	if( vaciaInS(*lista) ) printf("Error: Lista vacia \n");
	else{
		valor = (lista->in)->num;
		lista->in = (lista->in)->next;
		free( kill.in );
		if(lista->size == 1) startInS(lista);
		else --(lista->size);
	}
	return valor;
}

void PrintListOutS( ListaOutS lista ){
	if( vaciaOutS(lista) ) printf("Lista vacia\n");
	else{
		while( !vaciaOutS(lista) ){
			if( (lista.in)->next == NULL ) printf("[%d]-%c",(lista.in)->dig,186);
			else printf("[%d]->",(lista.in)->dig);
			lista.in = (lista.in)->next;
		}
		printf(" (%hd)\n",lista.size);
    }
}

void PrintListInS( ListaInS lista ){
	if( vaciaInS(lista) ) printf("%c\n",186);
	else{
		while( !vaciaInS(lista) ){
			if( (lista.in)->next == NULL ) printf("[%d]-%c",(lista.in)->num,186);
			else printf("[%d]->",(lista.in)->num);
			lista.in = (lista.in)->next;
		}
		printf(" (%hd)\n",lista.size);
    }
}

void PrintListLL( ListaOutS lista ){
	if( vaciaOutS(lista) ) printf("Lista vacia\n");
	else{
		printf("\n");
		while( !vaciaOutS( lista ) ){
			if( (lista.in)->next == NULL ){
				printf("[%d]->",(lista.in)->dig);
				PrintListInS( (lista.in)->Lista );
				printf(" %c\n",179);
				printf(" %c\n",205);
			}else{
				printf("[%d]->",(lista.in)->dig);
				PrintListInS( (lista.in)->Lista );
				printf(" %c\n",179);
			}
			lista.in = (lista.in)->next;
		}
		printf("(%hd)\n\n",lista.size);
    }
}

void Unificar( ListaOutS *Copy, ListaInS *Paste ){
	ListaInS *Save; ListaOutS Pivot; int A1,tam;	
	Pivot = *Copy; tam = 0;
	for( A1 = 0 ; A1 < D ; A1++ ){
		Save = &(Pivot.in)->Lista;
		if( !vaciaInS( *Save ) ){
			if( vaciaInS( *Paste ) ){
				*Paste = *Save;
			}else{
				(Paste->end)->next = Save->in;
				Paste->end = Save->end;
			}
			tam += Save->size;
			startInS( &(Pivot.in)->Lista );	
		}
		Pivot.in = (Pivot.in)->next;
	}
	Paste->size = tam;
}

void RadixShort( ListaOutS *Arreglo, ListaInS *Lista ){
	ListaInS search; ListaOutS Pivot;
	int max,num,div,i,j;
	search = *Lista;
	max = (search.in)->num;
	
	for( j = 0 ; !vaciaInS(search) && j < search.size ; search.in = (search.in)->next, j++ )
		if( (search.in)->num > max ) max = (search.in)->num;
		

	for( j = 0 ; max > 0 ; max /= D, j++);
	max = j;
	
	
	for( i = 0 ; i < max ; i++ ){
		div = pow(D,i);
		while( !vaciaInS( *Lista ) ){
			Pivot = *Arreglo;
			num = EliminaInsideInS( Lista );
			for( j = 1 ; (Pivot.in)->dig != (num/div)%D && j < Pivot.size ; j++ , Pivot.in = (Pivot.in)->next );
			InsertaInsideEndS( &(Pivot.in)->Lista , num );
			PrintListLL( *Arreglo );
		}
		Unificar( Arreglo , Lista );
		PrintListInS( *Lista );
	}
	
}


