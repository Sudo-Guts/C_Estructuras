/*
{ Arbol de Busqueda Binaria }
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

typedef int Dato; // Tipo definido de dato (^‿^)
/*	     ▲ 	
|	Puedes eliguir cualquier tipo de dato.
|	Ya sea int, float, char o incluso struct :o.
|	Nota: En la funcion print debes de cambiar 
|   el tipo de dato que quieres imprimir :(.
*/

short i = 0; // La mejor variable xD

typedef struct NodoArbol{
	Dato info;
	struct NodoArbol *Rigth;
	struct NodoArbol *Left;
}NodoA;

typedef NodoA *Tree;

short Leaf( Tree Root );
short Weight( Tree Root );
short Height( Tree Root );
short Search( Tree Root , Dato Val );

Tree CreaNodoA( Dato Data );

Tree mM( Tree Root , Dato *Val ); // menor de los Mayores
Tree Mm( Tree Root , Dato *Val ); // Mayor de los menores 

Tree Insert( Tree Root , Dato Data );
Tree Remove( Tree Root , Dato Val );

void PreOrden( Tree Root );
void InOrden( Tree Root );
void PostOrden( Tree Root );

void PrintLevel( Tree Root , short Level );
void PrintArbol( Tree Root );

void KillArbol( Tree Root );

short Leaf( Tree Root ){
	return ( (Root->Left == NULL) && (Root->Rigth == NULL) ) ? 1 : 0;
}

short Weight( Tree Root ){
	short Left = 0 , Rigth = 0;
	if( Root != NULL ){
		if( Root->Rigth != NULL )
			Rigth = Weight( Root->Rigth );
		if( Root->Left != NULL )
			Left = Weight( Root->Left );
	}
	return Rigth + Left + 1;
}

short Height( Tree Root ){
	short alturaIzq = 0, alturaDer = 0; 
	if( Root != NULL ){
		if( Root->Left != NULL )		
			alturaIzq = Height( Root->Left ) + 1;
		if( Root->Rigth != NULL )		
			alturaDer = Height( Root->Rigth ) + 1;
		return ( ( alturaIzq > alturaDer ) ? alturaIzq : alturaDer );
	}
}

short Search( Tree Root , Dato Val ){
	short res = 0;
	if( Root == NULL ) res = 0;
	else{
		if( Root->info == Val ) res = 1;
		else                            
			if( Val < Root->info )      
				res = Search( Root->Left , Val );
			else if( Val > Root->info ) 
				res = Search( Root->Rigth , Val );
	}
	return res;
}

Tree CreaNodoA( Dato Data ){
	Tree nodo;
	nodo = (Tree)malloc(sizeof(NodoA));
	if( nodo != NULL ){
		nodo->info = Data;
		nodo->Left = NULL;
		nodo->Rigth = NULL;
	}
	return nodo;
}

Tree mM( Tree Root , Dato *Val ){
	if( Root->Left != NULL ) Root->Left = mM( Root->Left , Val );
	else{
		Tree temp;
		temp = Root->Rigth;
		*Val = Root->info;
		free( Root );
		return temp;
	}
	return Root;
}

Tree Mm( Tree Root , Dato *Val ){
	if( Root->Rigth != NULL ) Root->Rigth = Mm( Root->Rigth , Val );
	else{
		Tree temp;
		temp = Root->Left;
		*Val = Root->info;
		free( Root );
		return temp;
	}
	return Root;
}

Tree Insert( Tree Root , Dato Data ){
	if( Root == NULL ) return CreaNodoA( Data );
	else if( Data < Root->info ) Root->Left = Insert( Root->Left , Data );
	else if( Data > Root->info ) Root->Rigth = Insert( Root->Rigth , Data );
	return Root;
}

Tree Remove( Tree Root , Dato Val ){
	if( Root == NULL ){
		printf("Elemento no localizado\n");
		return Root;
	}else{
		if( Val < Root->info ) Root->Left = Remove( Root->Left , Val );
		else if( Val > Root->info ) Root->Rigth = Remove( Root->Rigth , Val );
		else{ //Elemento localizado
			if( !Leaf( Root ) ){ // menor de los Mayores o Mayor de los menores
				Root->Rigth = mM( Root->Rigth , &Val );
				Root->info = Val;	
				return Root;
			}else{
				Tree temp;
				if( Root->Left == NULL ){
					temp = Root->Rigth;
					free( Root );
					return temp;
				}else{
					temp = Root->Left;
					free( Root );
					return temp;
				}				
			}
		}
	}
}

void PreOrden( Tree Root ){
	if( Root != NULL ){
		printf( "[%d]" , Root->info );
		PreOrden( Root->Left );
		PreOrden( Root->Rigth );
	}
}

void InOrden( Tree Root ){
	if( Root != NULL ){
		InOrden( Root->Left );
		printf( "[%d]" , Root->info );
		InOrden( Root->Rigth );
	}
}

void PostOrden( Tree Root ){
	if( Root != NULL ){
		PostOrden( Root->Left );
		PostOrden( Root->Rigth );
		printf( "[%d]" , Root->info );
	}
}

void PrintLevel( Tree Root , short Level ,  ){
	if( Root != NULL ){
		if( Level == 0 ) printf( "[%-3d]" , Root->info );
		else{
			PrintLevel( Root->Left , Level - 1 );

			PrintLevel( Root->Rigth , Level - 1 );
		}
	}
}

void PrintArbol( Tree Root ){
	short H,h,F,f,D,d,R,r;
	H = Height( Root );
	h = H;

	for( i = 0 ; i < H ; i++ , h-- , printf("\n") ){
		F = pow( 2 , h ) - 1;
		for( f = 0 ; f < F ; f++ ) printf( "   " );
		PrintLevel( Root , i ); printf("\n");
		D = F - pow( 2 , h - 3 );
		R = pow( 2 , i );
		for( r = 0 ; r < R ; r++ ){
			for( d = 0 ; d < D ; d++ ) printf( "   " );
			printf("/")
			for( );
			printf("\");
		}

	}
}

/*
void KillArbol( Arbol *Raiz ){
	if( Raiz != NULL ){
		if( Raiz->izq != NULL )
			Raiz->izq = KillArbol( Raiz->izq );
		if( Raiz->der != NULL )
			Raiz->der = KillArbol( Raiz->der );
		
	}
}
*/
