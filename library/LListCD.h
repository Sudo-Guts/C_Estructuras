#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoInside{
	int info;
	struct NodoInside *next;
}NodoIn;

typedef struct Inside{
	NodoIn *in;
	NodoIn *end;
	short size;
}ListaIn;

typedef struct NodoOutside{
	char grupo[10];
	struct NodoOutside *next;
	ListaIn Lista;
}NodoOut;

typedef struct Outside{
	NodoOut *in;
	NodoOut *end;
	short size;
}ListaOut;
