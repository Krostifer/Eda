#include <stdio.h>
#include <stdlib.h>

struct nodo{
	int dato;
	struct nodo *izq;
	struct nodo *der;
};

typedef struct nodo nodo;

nodo *T;

nodo *buscarNodo(nodo *A, int dato){

	nodo *aux;

	if (A == NULL)
		return NULL;
	else if(A->dato == dato)
		return A;
	
	aux = buscarNodo(A->izq, dato);
	
	if (aux != NULL)
		return aux;
	else
		return buscarNodo(A->der, dato);
}

nodo *agregarNodo(nodo *A, int padre, int dato){

	nodo *nuevo, *aux;
	nuevo = (nodo *)malloc(sizeof(nodo));
	nuevo->izq = NULL;
	nuevo->der = NULL;
	nuevo->dato = dato;

if (A == NULL){
	return nuevo;
}
else{
	aux = buscarNodo(A,padre);
	if(aux == NULL){
		printf("El nodo %i no existe",padre);
	return A;
}


else {
	if(aux->izq == NULL){
		aux->izq = nuevo;
		//return A;
}
else if(aux->der == NULL){
	aux->der = nuevo;
//return A;
}
else{
	printf("El nodo %i ya posee dos hijos", padre);
	//return A;
}
return A;
}
}



}

void mostrarPreOrden(nodo *T){
	//Preorden
	if(T == NULL){
		return;
	}
	if((T->izq == NULL) && (T->der == NULL))
			printf("%i ",T->dato);
		else{
		printf("%i ",T->dato);
		mostrarPreOrden(T->izq);
		mostrarPreOrden(T->der);
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////////
int esHoja(nodo *T){
	if((T->izq == NULL) && (T->der == NULL)){
		return 1;
	}

	else{
		return 0;
	}
}

int Altura(nodo *T){
	int alturaIz, alturaDr;

	//El arbol esta vacio
	if(T == NULL){
		return -1;
	}

	if(esHoja(T)){
		return 0;
	}

	alturaDr = Altura(T->der);
	alturaIz = Altura(T->izq);

	if(alturaDr>alturaIz){
		return alturaDr + 1;
	}

	else{
		return alturaIz + 1;
	}
}

int esAVL(nodo *T){
	int alturaIz, alturaDr;

	if(T == NULL){
		return 0;
	}

	alturaIz = Altura(T->izq);
	alturaDr = Altura(T->der);

	//diferencia de alturas
	if((alturaIz - alturaDr) > 1 || ((alturaIz - alturaDr)*-1) > 1){
		return 0;
	}

	if(esAVL(T->izq) && esAVL(T->der)){
		return 1;
	}


	return 1;
}

int contarHojas(nodo *T, int hojas, int comparar){

	int hojasActuales = hojas;

	if(T == NULL){
		return hojasActuales;
	}
	
	if(esHoja(T) && T->dato > comparar){
		hojasActuales += 1;
		return hojasActuales;
	}

	hojasActuales += contarHojas(T->izq, hojasActuales, comparar) + contarHojas(T->der, hojasActuales, comparar);

	return hojasActuales;
}



int main(){

	/*
	T = agregarNodo(T, 5, 40);
	T = agregarNodo(T, 40, 25);
	T = agregarNodo(T, 40, 50);
	T = agregarNodo(T, 25, 20);
	T = agregarNodo(T, 25, 30);
	T = agregarNodo(T, 50, 45);
	T = agregarNodo(T, 50, 75);

	*/

	T = agregarNodo(T, 5, 30);
	T = agregarNodo(T, 30, 10);
	T = agregarNodo(T, 30, 77);
	T = agregarNodo(T, 10, 5);
	T = agregarNodo(T, 10, 20);
	T = agregarNodo(T, 5, 3);
	T = agregarNodo(T, 77, 60);
	T = agregarNodo(T, 77, 90);

	mostrarPreOrden(T);
	printf("\n");

	printf("Hojas: %d\n", contarHojas(T, 0, 30));
	printf("%d\n", esAVL(T));

	return 0;
}