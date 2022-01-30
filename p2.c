#include <stdio.h>
#include <stdlib.h>

struct grafo{
	int n;	//cantidad de nodos
	int **A; //matriz de adyacencia
};


struct grafo *crearGrafo(char* nombreArchivo){
	
	FILE*pf;
	struct grafo *g;
	pf = fopen(nombreArchivo,"r");
	int n, aristas,i, j, k;
	fscanf(pf, "%d, %d", &n,&aristas); //Cantidad de nodos y aristas
	
	//crear grafo y asignar la memoria correspondiente
	g = (struct grafo *)malloc(sizeof(struct grafo));
	g->n = n;
	g->A = (int **)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++){
		g->A[i] = (int *)malloc(sizeof(int)*n);
		for(j=0;j<n;j++)
			g->A[i][j] = 0;
	}
	
	for(k=0;k<aristas;k++){
		fscanf(pf,"%d, %d",&i, &j);
		g->A[i-1][j-1] = 1;
		g->A[j-1][i-1] = 1;
	}
	
	fclose(pf);
	return  g;
}

void mostrarGrafo(struct grafo *G){
	
	int i,j;
	
	printf("\nNodos: %d\n", G->n);
	
	for (i=0;i<G->n;i++){
		
		for (j=0;j<G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
		
}

int comprobarConexiones(int *lista, int n){
	for(int i=0; i <n; i++){
		if(lista[i] == 0){
			return 0;
		}
	}
	return 1;
}

int verticeConMasAristas(struct grafo *G, int *estadoDeConexion){
	int  indiceMayor = -1, aristasMayor = -1;

	for(int i=0; i < G->n; i++){
		int aristasActuales = 0;

		for(int j=i+1; j < G->n; j++){
			if(G->A[i][j] == 1){
				aristasActuales += 1;
			}
		}

		if(aristasActuales > aristasMayor){
			aristasMayor = aristasActuales;
			indiceMayor = i;
		}

		else if(aristasActuales == aristasMayor){
			if(estadoDeConexion[indiceMayor] == 1 && estadoDeConexion[i] == 0){
				aristasMayor = aristasActuales;
				indiceMayor = i;
			}
		}
	}

	return indiceMayor;
}

int conectarInternet(struct grafo *G){
	int *estadoDeConexion;
	int cantidadCentrales = 0;
	estadoDeConexion = (int *)malloc(G->n * sizeof(int));

	for(int i=0; i < G->n; i++){
		estadoDeConexion[i] = 0;
	}

	while(comprobarConexiones(estadoDeConexion, G->n) == 0){
		int indiceNuevaCentral = verticeConMasAristas(G, estadoDeConexion);
		estadoDeConexion[indiceNuevaCentral] = 2;
		printf("Central de internet agregada en el vertice: %d\n", indiceNuevaCentral+1);
		for(int j = 0; j < G->n; j++){
			if(G->A[indiceNuevaCentral][j] == 1){
				if(estadoDeConexion[j] == 0){
					estadoDeConexion[j] = 1;
				}
			}
		}
		cantidadCentrales += 1;
	}
	return cantidadCentrales;
}

int main(int argc, char *argv[]){

	struct grafo *G;
	mostrarGrafo(G);
	printf("Cantidad de centrales construidas: %d\n", conectarInternet(G));
	
	return 0;
}