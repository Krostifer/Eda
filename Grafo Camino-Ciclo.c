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

int esCamino(struct grafo *G, int *S, int largo){
	//int largo = sizeof(S)/ sizeof(int);

	for(int i = 0; i < largo-1;i++){
		if(G->A[S[i]-1][S[i+1]-1] == 0){
			return 0;
		}
	}
	return 1;
}

int esCiclo(struct grafo *G, int *S, int largo){
	

	if(S[0] != S[largo-1]){
		return 0;
	}

	return esCamino(G, S, largo);
}


int main(int argc, char *argv[]){

	struct grafo *G;

	G = crearGrafo(argv[1]);
	mostrarGrafo(G);

	/*
	int camino[4] = {1,2,3,1};

	int resultado = esCiclo(G, camino, 4);

	if(resultado == 1){
		printf("Es camino\n");
	}

	else{
		printf("No es camino\n");
	}
	*/

	return 0;

}