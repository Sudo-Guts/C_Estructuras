/*
{ Arbol Binario (Adelson-Velskii) }
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int Dato; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: En la funcion print debes de cambiar 
|   el tipo de dato que quieres imprimir :(.
*/

typedef struct NodoArbol{
	Dato info;
	struct NodoArbol *Rigth;
	struct NodoArbol *Left;
}NodoA;

typedef NodoA *Arbol;

short Leaf( Arbol Raiz );
short Search( Arbol Raiz );
short Peso( Arbol Raiz );
short Altura( Arbol Raiz );
short FactorE( Arbol Raiz );

Arbol CreaNodoA( int data );

Arbol mM( Arbol Raiz, int *val );
Arbol Mm( Arbol Raiz, int *val );

Arbol RotacionDer( Arbol NodoA );
Arbol RotacionIzq( Arbol NodoA );

Arbol Insertar( Arbol Raiz );
Arbol Eliminar( Arbol Raiz, int val );

void PreOrden( Arbol Raiz );
void InOrden( Arbol Raiz );
void PostOrden( Arbol Raiz );
void PrintLevel( Arbol Raiz, short level );
void PrintArbol( Arbol Raiz );

void KillArbol( Arbol Raiz );

short Leaf( Arbol Raiz ){
	return ( (Raiz->izq == NULL) && (Raiz->der == NULL) )? 1:0;
}

short Search( Arbol Raiz, int val ){
	short res = 0;
	if( Raiz == NULL ) res = 0;
	else{
		if( Raiz->info == val ) res = 1;
		else                            
			if( val < Raiz->info )      
				res = Search( Raiz->izq, val );
			else if( val > Raiz->info ) 
				res = Search( Raiz->der, val );
	}
	return res;
}

short Peso( Arbol Raiz ){
	short Izq = 0,Der = 0;
	if( Raiz != NULL ){
		if( Raiz->der != NULL )
			Der = Peso( Raiz->der );
		if( Raiz->izq != NULL )
			Izq = Peso( Raiz->izq );
	}
	return Der + Izq + 1;
}


short Altura( Arbol Raiz ){
	short alturaIzq = 0, alturaDer = 0;     
	if( Raiz != NULL ){
		if( Raiz->izq != NULL ) 				
			alturaIzq = Altura( Raiz->izq );
		if( Raiz->der != NULL )					
			alturaDer = Altura( Raiz->der );
			
		if( alturaIzq > alturaDer )				
			return alturaIzq + 1;				
		else
			return alturaDer + 1;	
	}				
}

short FactorE( Arbol Raiz ){
	return Altura( Raiz->der ) - Altura( Raiz->izq );
}

Arbol CreaNodoA( int data ){
	Arbol nodo;
	nodo = (Arbol)malloc( sizeof(NodoA) );
	if( nodo != NULL ){
		nodo->info = data;
		nodo->izq = NULL;
		nodo->der = NULL;
	}
	return nodo;
}

Arbol mM( Arbol Raiz, int *val ){
	if( Raiz->izq != NULL ) 
		Raiz->izq = mM( Raiz->izq, val );
	else{
		Arbol Temp;
		Temp = Raiz->der;
		*val = Raiz->info;
		free( Raiz );
		return Temp;
	}
	return Raiz;
}

Arbol Mm( Arbol Raiz, int *val ){
	if( Raiz->der != NULL )
		Raiz->der = Mm( Raiz->der, val );
	else{
		Arbol Temp;
		Temp = Raiz->izq;
		*val = Raiz->info;
		free( Raiz );
		return Temp;
	}
	return Raiz;
}

Arbol RotacionDer( Arbol NodoA ){
	Arbol NodoB = NodoA->izq;
	Arbol HijoB = NodoB->der;
	NodoB->der = NodoA;
	NodoA->izq = HijoB;
	return NodoB;
}

Arbol RotacionIzq( Arbol NodoA ){
	Arbol NodoB = NodoA->der;
	Arbol HijoB = NodoB->der;
	NodoB->izq = NodoA;
	NodoA->der = HijoB;
	return NodoB;
}

Arbol Insertar( Arbol Raiz, int data ){
	if( Raiz == NULL ) return CreaNodoA( data );
	else{
		short FE = 0;
		if( data < Raiz->info ) 
			Raiz->izq =  Insertar( Raiz->izq, data );
		else if( data > Raiz->info ) 
			Raiz->der =  Insertar( Raiz->der, data );
		FE = FactorE( Raiz );
		if( FE > 1 ){
			if( data > (Raiz->der)->info ) return RotacionIzq( Raiz );
			else{
				Raiz->der = RotacionDer( Raiz->der );
				return RotacionIzq( Raiz );
			}
		}
		if( FE < -1 ){
			if( data > (Raiz->izq)->info ) return RotacionDer( Raiz );
			else{
				Raiz->izq = RotacionIzq( Raiz->izq );
				return RotacionDer( Raiz );
			}
		}		
	}
}

Arbol Eliminar( Arbol Raiz, int val ){
	if( Raiz == NULL ){
		printf("Elemento no localizado\n");
		return Raiz;
	}else{
		if( val < Raiz->info )
			Raiz->izq = Eliminar( Raiz->izq, val );
		else if( val > Raiz->info )
				Raiz->der = Eliminar( Raiz->der, val );
		else{ //Elemento localizado
			if( !Leaf( Raiz ) ){// menor de los Mayores o Mayor de los menores
				Raiz->der = mM( Raiz->der, &val );
				Raiz->info = val;	
				return Raiz;
			}else{
				Arbol Temp;
				if( Raiz->izq == NULL ){
					Temp = Raiz->der;
					free( Raiz );
					return Temp;
				}else{
					Temp = Raiz->izq;
					free( Raiz );
					return Temp;
				}				
			}
		} 
	}	
}

void PreOrden( Arbol Raiz ){
	if( Raiz != NULL ){
		printf("[%d]",Raiz->info);
		PreOrden( Raiz->izq );
		PreOrden( Raiz->der );
	}
}

void InOrden( Arbol Raiz ){
	if( Raiz != NULL ){
		InOrden( Raiz->izq );
		printf("[%d]",Raiz->info);
		InOrden( Raiz->der );
	}
}

void PostOrden( Arbol Raiz ){
	if( Raiz != NULL ){
		PostOrden( Raiz->izq );
		PostOrden( Raiz->der );
		printf("[%d]",Raiz->info);
	}
}

void PrintLevel( Arbol Raiz, short level ){
	if( Raiz != NULL ){
		if( level == 0 ) printf("-{%d}-",Raiz->info);
		else{
			PrintLevel( Raiz->izq, level - 1 );
			PrintLevel( Raiz->der, level - 1 );
		}
	}
}

void PrintArbol( Arbol Raiz ){
	short H,i;
	H = Altura( Raiz );
	for( i = 0 ; i < H ; i++, printf("\n") ) 
		PrintLevel( Raiz, i );
}

void KillArbol( Arbol Raiz ){
	
	
	
}

