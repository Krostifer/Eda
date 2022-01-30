#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 50
#define CANT_NODOS 10

struct grafo{
	int n;	//cantidad de nodos
	int ***A; //matriz de adyacencia
};

//Funcion que comprueba si un nodo ya se encuetra registrado en la lista de nodos
//Recibe como argumentos la lista de nodos registrados, el nombre del nodo que se desea buscar y el largo de la lista de nodos
//Retorna un 1 si es que el nodo ya esta registrado o un 0 en el caso contrario
int existeNodo(char listaNodos[][MAX_STRING], char nodo[MAX_STRING], int largo) {
	for(int i=0; i < largo; i++) {
		if(strcmp(listaNodos[i], nodo) == 0) {
			return 1;
		}
	}
	return 0;
}

//Funcion que retorna el indice que tiene un nodo dentro de una lista de nodos(representa su posicion en la matriz de adyacencia)
//Recibe como argumentos la lista de nodos registrados, el nodo al cual se desea conocer su indice y el largo de la lista de nodos
//Retorna un entero con el indice del nodo o un -1 en caso de que el nodo no se encuentre en la lista
int indiceNodo(char listaNodos[][MAX_STRING], char nodoBuscado[MAX_STRING], int largo) {
	for(int i = 0; i < largo; i++) {
		if(strcmp(listaNodos[i], nodoBuscado) == 0) {
			return i;
		}
	}
	return -1;
}

//Funcion que crea una representacion de grafo a partir de un archivo de entrada
//Recibe como argumentos el nombre del archivo de entrada y la lista de nodos registrados
//Retorna un grafo con la informacion leida
struct grafo *crearGrafo(char const* nombreArchivo, char nodos[][MAX_STRING]){
	
	FILE *pf;
	struct grafo *g;
	pf = fopen(nombreArchivo,"r");

	//Si es que no se pudo abrir el archivo de entrada
	if(pf == NULL){
		g->n = 0;
		return g;
	}

	int n, indiceOri, indiceDes, distancia, costo;
	int nodosRegistrados = 0;

	fscanf(pf, "%d", &n); //Cantidad de nodos

	if(n <= 0){
		g->n = -1;
		return g;
	}
	
	//Crear grafo, asignar la memoria correspondiente y lo inicializa en 0
	g = (struct grafo *)malloc(sizeof(struct grafo));
	g->n = n;
	g->A = (int ***)malloc(sizeof(int **)*n);
	for(int i = 0; i < n; i++){
		g->A[i] = (int **)malloc(sizeof(int *)*n);
		for(int j = 0; j < n; j++){
			g->A[i][j] = (int *)malloc(sizeof(int)*2);
			g->A[i][j][0] = 0;
			g->A[i][j][1] = 0;
		}
	}
	
	char origen[MAX_STRING];
	char destino[MAX_STRING];

	while(feof(pf) == 0){

		fscanf(pf, "%s", origen);
		if(existeNodo(nodos, origen, n) == 0){
			strcpy(nodos[nodosRegistrados], origen);
			nodosRegistrados++;
		}

		fscanf(pf, "%s", destino);
		if(existeNodo(nodos, destino, n) == 0){
			strcpy(nodos[nodosRegistrados], destino);
			nodosRegistrados++;
		}

		indiceOri = indiceNodo(nodos, origen, nodosRegistrados);
		indiceDes = indiceNodo(nodos, destino, nodosRegistrados);

		fscanf(pf, "%d", &g->A[indiceOri][indiceDes][0]);
		fscanf(pf, "%d", &g->A[indiceOri][indiceDes][1]);
	}

	fclose(pf);
	return  g;
}

//Funcion que leer el archivo de entrada que contiene el combustible de la nave y las estaciones de recarga
//Recibe como argumentos el nombre del archivo de entrada, la direccion de memoria de la variable donde se almacenara el combutible, el arreglo con los nodos registrados, el largo de este arreglo
//		y la direccion de memoria donde se almacenara el largo del arreglo de las estaciones de recarga
//Retorna un arreglo de enteros con las posiciones de los "planetas" en los que se puede recargar combustible y se actualiza por referencia el valor del combutible total de la nave como el del largo de las estaciones de recarga
int* leerCombustible(char const* nombreArchivo, int *combustible, char listaNodos[][MAX_STRING], int largoNodos, int *largoRecargas) {
	FILE *pf;
	pf = fopen(nombreArchivo,"r");

	//Si es que no se pudo abrir el archivo de entrada
	if(pf == NULL){
		int *E = (int *)malloc(sizeof(int)*1);
		E[0] = -1;
		return E;
	}

	fscanf(pf, "%d", combustible); //Capacidad maxima de combustible

	char estacion[MAX_STRING];
	int *estacionesRecarga = (int *)malloc(sizeof(int)*(largoNodos-2));	//A lo maximo pueden ser estaciones de recarga todos los planetas menos el la tierra y pizza-planet

	while(feof(pf) == 0) {
		fscanf(pf, "%s", estacion);
		estacionesRecarga[*largoRecargas] = indiceNodo(listaNodos, estacion, largoNodos);
		*largoRecargas = *largoRecargas +1;
	}

	fclose(pf);
	return estacionesRecarga;
}

//Funcion que muestra la matriz de adyacencia de un grafo
//Recibe como argumento un grafo
void mostrarGrafo(struct grafo *G){
	
	printf("\nNodos: %d\n", G->n);
	
	for (int i = 0; i < G->n; i++){
		
		for (int j = 0; j < G->n; j++){
			printf("[%d, %d] ",G->A[i][j][0], G->A[i][j][1]);
		}
		printf("\n");
	}
}

//Funcion que muestra los nodos existentes en el archivo de entrada
//Recibe como argumentos la lista de nodos y el largo de esta
void mostrarNodosRegistrados(char listaNodos[][MAX_STRING], int largo) {
	for(int i = 0; i < largo; i++) {
		printf("El planeta: %s tiene el indice: %d\n", listaNodos[i], i);
	}
}


int main(int argc, char const *argv[])
{
	struct grafo *G;
	char nodos[CANT_NODOS][MAX_STRING];

	G = crearGrafo(argv[1], nodos);

	if(G->n == 0) {
		printf("El archivo de entrada no exite.\n");
		return 1;
	}

	if(G->n == -1) {
		printf("No hay nodos en el mapa ingresado.\n");
		return 1;
	}

	int combustibleMax = 0;
	int largoRecargas = 0;

	int* estacionesRecarga = leerCombustible(argv[2], &combustibleMax, nodos, G->n, &largoRecargas);

	if(estacionesRecarga[0] == -1) {
		printf("El archivo de entrada no exite.\n");
		return 1;
	}

	int comienzo = indiceNodo(nodos, "tierra", CANT_NODOS);
	int destino = indiceNodo(nodos, "pizza_planet", CANT_NODOS);

	mostrarGrafo(G);
	mostrarNodosRegistrados(nodos, G->n);
	
	return 0;
}