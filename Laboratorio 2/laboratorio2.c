#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructura de datos que representa una cancion dentro de una lista simplemente enlazada
typedef struct nodo{
	int puntaje;
	char nombre[50];
	int duracion;
	int idArtista;
	char artista[25];
	int idGenero;
	char genero[25];
	struct nodo *sig;
} nodo;

//Estructura de datos que representa un entero dentro de una lista simplemente enlazada
typedef struct nodoDato{
	int dato;
	struct nodoDato *sig;
} nodoDato;

//Funcion que crea una estructura del tipo nodo
//Recibe como argumento el valor del puntaje de la cancion, su nombre, su duracion, el identificador de su artista, el nombre de su artista, el identificador de su genero y el nombre del genero
//Retorna una estructura del tipo nodo con la informacion entregada
nodo *crearNodo(int puntaje, char *nombre, int duracion, int idArtista, char *artista, int idGenero, char *genero){
	nodo *aux;
	aux = (nodo*)malloc(sizeof(nodo));
	aux->puntaje = puntaje;
	strcpy(aux->nombre, nombre);
	aux->duracion = duracion;
	aux->idArtista = idArtista;
	strcpy(aux->artista, artista);
	aux->idGenero = idGenero;
	strcpy(aux->genero, genero);
	aux->sig = NULL;

	return aux;
}

//Funcion que crea una estructura del tipo nodoDato
//Recibe como argumento el valor que se desea almacenar en el nodo
//Retorna una estructura del tipo nodoDato con el valor entregado
nodoDato *crearNodoDato(int dato){
	nodoDato *aux;
	aux = (nodoDato*)malloc(sizeof(nodoDato));
	aux->dato = dato;
	aux->sig = NULL;

	return aux;
}

//Funcion que agrega un nodo al final de una lista simplemente enlazada de nodos
//Recibe como argumentos una lista simplemente enlazada de nodos y el nodo a agregar al final
//Retorna la misma lista simplemente enlazada de nodos con el nuevo elemento agregado al final de esta
nodo *agregarFinalNodo(nodo *L, nodo *nodoAgregar){

	//En caso de que la lista este vacia
	if(L == NULL){
		L = nodoAgregar;
		return L;
	}

	nodo *aux = L;
	//Caso general
	while(aux->sig != NULL){
		aux = aux->sig;
	}

	aux->sig = nodoAgregar;

	return L;
}

//Funcion que agrega un nodoDato al final de una lista simplemente enlazada de nodosDato
//Recibe como argumentos una lista simplemente enlazada de nodoDato y el nodoDato a agregar al final
//Retorna la misma lista simplemente enlazada de nodoDato con el nuevo elemento agregado al final de esta
nodoDato *agregarFinalDato(nodoDato *L, nodoDato *nodoAgregar){
	nodoDato *aux = L;

	if(aux == NULL){
		L = nodoAgregar;
		return L;
	}

	while(aux->sig != NULL){
		aux = aux->sig;
	}

	aux->sig = nodoAgregar;

	return L;
}

//Funcion que transforma la duracion en "minutos:segundos" de una cacion a un entero con su duracion en segundos
//Recibe como argumento un string con la duracion de una cancion
//Retorna un entero con la duracion de una cancion en segundos
int tiempoSegundos(char* tiempo){
	int largo = strlen(tiempo);
	int minutos = 0; 
	int segundos = 0;
	int i = 0;

	//Se recorre la parte del string que contiene los minutos
	while (tiempo[i] != ':')
	{
		//Se transforma el caracter a un numero entero
		int aux = tiempo[i] - 48;
		minutos = (minutos*10) + aux;
		i += 1;
	}
	//Se suma uno para no leer el caracter ':'
	i += 1;

	//Se lee el resto del string que corresponde a los segundos 
	while (i < largo)
	{
		//Se transforma el caracter en un entero
		int aux = tiempo[i] - 48;
		segundos = (segundos*10) + aux;
		i += 1;
	}
	//Se transforman los minutos en segundos y se suma con el resto de los segundos
	segundos = (minutos*60) + segundos;

	return segundos;
}

//Funcion que transforma la duracion en segundos de una cacion a un string con su duracion en minutos
//Recibe como argumento un entero que representa la duracion en segundos de una cancion
//Retorna un string con la duracion de la cancion en "minutos:segundos"
char* segundosTiempo(int tiempo){
	char * duracionString = malloc(8);
	char segundosChar[2];

	//Se calculan la cantidad de minutos y segundos
	int minutos = tiempo/60; 
	int segundos = tiempo%60;

	//Se almacenan los minutos dentro del string de duracion
    sprintf(duracionString, "%d", minutos);	
    //Se agrega el separador de minutos-segundos
	strcat(duracionString, ":");

	//En caso de que los segundos sean menor a 10, se agrega un cero delante de ellos
	if(segundos < 10){
		strcat(duracionString, "0");
	}

	//Se convierten los segundos a string y se agregan al string de la duracion
    sprintf(segundosChar, "%d", segundos);	
    strcat(duracionString, segundosChar);

	//Se retorna la duracion como string
	return duracionString;	
}

//Funcion que obtiene el indice del elemento con mayor puntuacion y precedencia alfabetica dentro de una lista simplemente enlazada de nodos
//Recibe como argumento una lista simplemente enlazada de nodos
//Retorna un entero que representa la posicion del elemento con mayor puntuacion dentro de la lista simplemente enlazada de nodos
int obtenerIndiceMayor(nodo *L){
	//Caso donde solo haya un elemento en la lista
	if(L->sig == NULL){
		return 1;
	}

	nodo *aux = L->sig;
	//Variable para recorrer la lista
	int i = 2;
	//Variable que indica el indice del mayor elemento de la lista
	int indiceMayor = 1;
	//Se establece el primer elemento como el mayor para ser utilizado como pivote
	int puntajeMayor = L->puntaje;
	//Se guarda el nombre del artista del elemento mayor para compararlo alfabeticamente en caso de ser necesario
	char artistaMayor[25];
	strcpy(artistaMayor, L->artista);
	//Se guarda la duracion del elemento mayor para comparar en caso de ser necesario y se inicializa con la duracion del primer elemento
	int duracionMayor = aux->duracion;

	//Se recorre la lista mientras no se llegue al final de esta
	while(aux != NULL){
		//Se registra la informacion del nuevo elemento mayor si este tiene una mayor puntuacion
		if(aux->puntaje > puntajeMayor){
			indiceMayor = i;
			strcpy(artistaMayor, aux->artista);
			duracionMayor = aux->duracion;
			puntajeMayor = aux->puntaje;
		}
		//Si es que tienen igual puntuacion se comprueba su orden alfabetico
		else if(aux->puntaje == puntajeMayor){
			//Si el elemento actual va antes alfabeticamente, este se registra como el nuevo elemento mayor
			if(strcmp(aux->artista, artistaMayor) == -1){
				indiceMayor = i;
				duracionMayor = aux->duracion;
				strcpy(artistaMayor, aux->artista);
				puntajeMayor = aux->puntaje;
			}
			//Si ambas canciones tienen el mismo artista, se comprueba su duracion
			else if(strcmp(aux->artista, artistaMayor) == 0){
				if(aux->duracion < duracionMayor){
					indiceMayor = i;
					duracionMayor = aux->duracion;
					strcpy(artistaMayor, aux->artista);
					puntajeMayor = aux->puntaje;
				}
			}
		}
		//Se avanza al siguiente elemento de la lista
		aux = aux->sig;
		//Se actualiza el indice
		i +=1;
	}
	return indiceMayor;
}

//Funcion que agrega la informacion del nombre del artista a las canciones que tienen el id de este artista
//Recibe como argumentos una lista simplemente enlazada de nodos que contiene las canciones, el identificador del artista y el nombre de este
//Retorn ala misma lista simplemente enlazada con la informacion del artista actualizada en las canciones pertenecientes a este artista
nodo *agregarArtistas(nodo *L, int id, char *artista){
	nodo *aux = L;

	while(aux != NULL){
		if(aux->idArtista == id){
			strcpy(aux->artista, artista);
		}
		aux = aux->sig;
	}
	return L;
}

//Funcion que agrega la informacion el nombre del genero a las canciones que tienen el id de este genero
//Recibe como argumentos una lista simplemente enlazada de nodos que contiene las canciones, el identificador del genero y el nombre del genero
//Retorna la misma lista simplemente enlazada con las informacion del genero actualizada en las canciones que pertencen a este genero
nodo *agregarGeneros(nodo *L, int id, char *genero){
	nodo *aux = L;

	while(aux != NULL){
		if(aux->idGenero == id){
			strcpy(aux->genero, genero);
		}
		aux = aux->sig;
	}
	return L;
}

//Funcion que lee el archivo de entrada que contiene las canciones con su informacion y crea una lista de nodos con estas canciones
//Recibe como argumento el nombre del archivo de entrada
//Retorna una lista simplemente enlazada de nodos donde cada nodo contiene la informacion de una cancion
nodo *leerCanciones(char const* archivoCanciones){
	FILE *fp;
	fp = fopen(archivoCanciones, "r");

	nodo *listaCanciones = NULL;

	if(fp == NULL){
		return listaCanciones;
	}

	int ignorar;
	fscanf(fp, "%d", &ignorar);

	char nombre[25], duracionString[8];
	int duracion;
	int idArtista, idGenero, puntaje;

	while(feof(fp) == 0){
		fscanf(fp, "%s", nombre);
		fscanf(fp, "%s", duracionString);
		fscanf(fp, "%d", &idArtista);
		fscanf(fp, "%d", &idGenero);
		fscanf(fp, "%d", &puntaje);

		duracion = tiempoSegundos(duracionString);
		nodo *aux = crearNodo(puntaje, nombre, duracion, idArtista, "", idGenero, "");
		listaCanciones = agregarFinalNodo(listaCanciones, aux);
	}

	fclose(fp);
	return listaCanciones;
}

//Funcion que lee el archivo de entrada que contiene el id del artista con su nombre y agrega esta informacion a las canciones almacenadas
//Recibe como argumentos el nombre del archivo de entrada y una lista simplemente enlazada de nodos que contiene las canciones
//Retorna la misma lista simplemente enlazada de nodos con la informacion de sus canciones actualizada con sus respectivos artistas
nodo *leerArtistas(char const* archivoArtistas, nodo *listaCanciones){
	FILE *fp;
	fp = fopen(archivoArtistas, "r");

	if(fp == NULL){
		nodo *L = NULL;
		return L;
	}

	int ignorar;
	fscanf(fp, "%d", &ignorar);

	char artista[25];
	int idArtista;

	while(feof(fp) == 0){
		fscanf(fp, "%d", &idArtista);
		fscanf(fp, "%s", artista);
		listaCanciones = agregarArtistas(listaCanciones, idArtista, artista);
	}
	fclose(fp);
	return listaCanciones;
}

//Funcion que lee el archivo de entrada que contiene el id de los generos con su nombre del genero y agrega esta informacion a las canciones almacenadas
//Recibe como argumentos el nombre del archivo de entrada y una lista simplemente enlazada de nodos que contiene las canciones 
//Retorna la misma lista simplemente enlazada de nodos con la informacion de sus canciones actualizada con sus respectivos generos
nodo *leerGeneros(char const* archivoGeneros, nodo *listaCanciones){
	FILE *fp;
	fp = fopen(archivoGeneros, "r");

	if(fp == NULL){
		nodo *L = NULL;
		return L;
	}

	int ignorar;
	fscanf(fp, "%d", &ignorar);

	char genero[25];
	int idGenero;

	while(feof(fp) == 0){
		fscanf(fp, "%d", &idGenero);
		fscanf(fp, "%s", genero);
		listaCanciones = agregarGeneros(listaCanciones, idGenero, genero);
	}
	fclose(fp);
	return listaCanciones;
}


//Funcion que genera una nueva lista simplemente enlazada de nodos con las cancion ordenadas por su puntaje de mayor a menor y alfabeticamente en caso de tener igual puntaje
//Recibe como argumento una lista simplemente enlazada de nodos
//Retorna una nueva lista simplemente enlazada de nodos con los elementos ordenados
nodo *ordenarCanciones(nodo *L){
	nodo *listaOrdenada = NULL;
	//Se busca el elemento mayor y se agrega a la nueva lista hasta que la original este vacia
	while(L != NULL){
		nodo *aux = L;
		nodo *otroAux = NULL;
		//Variable para recorrer la lista por sus posiciones
		int j = 1;
		//Se calcula el indice del elemento con mayor puntaje dentro de la lista
		int indiceMayor = obtenerIndiceMayor(L);
	
		//En caso de que el mayor elemento sea el primero
		if(indiceMayor == 1){

			otroAux = L;
			L = otroAux->sig;
			otroAux->sig = NULL;
			//Se agrega el elmento a la nueva lista
			agregarFinalNodo(listaOrdenada, otroAux);
		}

		else{

			//Se busca la posicion anterior al elemento mayor de la lista
			while(j < indiceMayor-1){
				aux = aux->sig;
				j += 1;
			}

			//Caso general donde el elemento mayor se encuentra en una diferente posicion
		
			otroAux = aux->sig;
			aux->sig = otroAux->sig;
			otroAux->sig = NULL;
			//Se agrega el elmento a la nueva lista
			listaOrdenada = agregarFinalNodo(listaOrdenada, otroAux);	
		}
	}
	//Se retorna la nueva lista con los elemento ordenados
	return listaOrdenada;
}

//Funcion que genera el archivo de salida con la informacion de las canciones ordenadas por su puntaje de mayor a menor
//Recibe como argumento una lista simplemente enlazada de nodos que contienen las canciones
//No retorna nada, pero genera un archivo de texto con la informacion de las canciones ordenadas
void generarSalidaCanciones(nodo *L){
	FILE* salida;
	//Se abre el archivo "salida.out" en modo escritura (lo creara si no existe o lo remplazara si existe)
	salida = fopen ("salida.out", "w");

	nodo *aux = L;

	while(aux != NULL){
		fprintf(salida, "%d;%s;%s;%s;%s\n", aux->puntaje, aux->nombre, segundosTiempo(aux->duracion), aux->artista, aux->genero);
		aux = aux->sig;
	}
	fclose(salida);
	return;
}

//Funcion que lee el archivo de entrada con las preferencias para la playlist y genera una lista con los ids de los generos preferidos
//Recibe como argumentos el nombre del archivo de entrada y la direccion de memoria donde se almacenara la duracion maxima de la playlist
//Retorna una lista simplemente enlazada de nodosDato con los ids de los generos preferidos y se actualiza por referencia la duracion maxima de la playlist
nodoDato *leerPreferencias(char const* archivoPreferencias, int *duracionPl){
	FILE *fp;
	fp = fopen(archivoPreferencias, "r");

	nodoDato *listaPreferencias = NULL;

	if(fp == NULL){
		return listaPreferencias;
	}

	char duracion[8];
	fscanf(fp, "%s", duracion);
	*duracionPl  = tiempoSegundos(duracion);

	
	int aux = 0;

	while(feof(fp) == 0){
		fscanf(fp, "%d", &aux);
		nodoDato *otroAux = crearNodoDato(aux);
		listaPreferencias = agregarFinalDato(listaPreferencias, otroAux);
	}

	fclose(fp);
	return listaPreferencias;
}

//Funcion que genera un archivo de texto plano con las canciones que componen la playlist con las preferencias
//Recibe como argumentos una lista simplemente enlazada de nodos que contiene las canciones ordenadas, una lista simplemente enlazada de nodosDatos que contiene el id de generos preferidos y la duracion en segundos que debe tener la playlist
//No retorna nada, pero genera un archivo de texto
void crearPlaylist(nodo *listaCanciones, nodoDato *listaPreferencias, int duracionPlaylist){
	//Se crea una lista simplemente enlazada para almacenar las canciones ya agregadas
	nodo *cancionesAgregadas = NULL;
	//Se establece la duracion inicial de la playlist
	int duracionActual = 0;

	//Se crea el archivo de salida
	FILE *salida;
	salida = fopen ("playlist.out", "w");
	
	//Se crean nodos auxiliares
	nodo *auxCancion; 
	nodo *otroAux = NULL;

	//Se agregan canciones mientras no se haya alcanzado el limite de tiempo
	while (duracionActual < duracionPlaylist){
		//Caso en donde se agregaron todas las canciones con genero preferido, se procede a repetir las canciones ya agregadas
		if (listaPreferencias == NULL){
			nodo *cancionRepetida;
			//Se agregan canciones repetidas mientras no se haya alcanzado el limite de tiempo
			while(duracionActual < duracionPlaylist){
				cancionRepetida = cancionesAgregadas;
				//Se escribe la informacion de la cancion en el archivo de salida
				fprintf(salida, "%d;%s;%s;%s;%s\n", cancionRepetida->puntaje, cancionRepetida->nombre, segundosTiempo(cancionRepetida->duracion), cancionRepetida->artista, cancionRepetida->genero);
				//Se actualiza la duracion actual de la playlist
				duracionActual += cancionRepetida->duracion;
				//Se actualiza el primer elemento de la lista de canciones repetidas
				cancionesAgregadas = cancionesAgregadas->sig;
				cancionRepetida->sig = NULL;
				//Se agrega la cancion agregada al final de la lista de canciones ya agregadas
				cancionesAgregadas = agregarFinalNodo(cancionesAgregadas, cancionRepetida);
			}
			//En caso de que se supero el limite de tiempo, se escribe por cuando tiempo se excedio la ultima cancion agregada
			if (duracionActual > duracionPlaylist){
				fprintf(salida, "%s\n", segundosTiempo((duracionActual-duracionPlaylist)));
			}
			//Se cierra el archivo de salida
			fclose(salida);

			return;
		}
		//Se obtiene el id del genero preferido que se encuentra en el primer lugar de la lista de generos preferidos
		nodoDato *auxPref = listaPreferencias;
		auxCancion = listaCanciones;

		//Caso en el que el primer elemento de la lista de canciones cumple con el genero buscado
		if(auxCancion->idGenero == auxPref->dato){
			otroAux = auxCancion->sig;
			auxCancion->sig = otroAux->sig;
			//Se escribe la informacion de la cancion en el archivo de salida
			fprintf(salida, "%d;%s;%s;%s;%s\n", otroAux->puntaje, otroAux->nombre, segundosTiempo(otroAux->duracion), otroAux->artista, otroAux->genero);
			//Se actualiza el nuevo primer elemento de la lista de ids de generos preferidos
			listaPreferencias = listaPreferencias->sig;
			auxPref->sig = NULL;
			//Se agrega el id del genero acual al final de la lista de preferencias
			listaPreferencias = agregarFinalDato(listaPreferencias, auxPref);
			//Se actualiza la duracion actual de la playlist
			duracionActual += otroAux->duracion;
			otroAux->sig = NULL;
			//Se agrega la cancion agregada al final de la lista de canciones ya agregadas
			cancionesAgregadas = agregarFinalNodo(cancionesAgregadas, otroAux);
		}

		//Caso general donde el primer elemento de la lista no cumple con el genero buscado
		else{
			//Se recorre la lista buscando el genero buscado en la cancion siguiente a la actual
			while(auxCancion->sig != NULL && auxCancion->sig->idGenero != auxPref->dato){
				auxCancion = auxCancion->sig;
			}
			//Si es que se encontro el genero buscado, se procede agregar a la playlist
			if(auxCancion->sig != NULL){
				otroAux = auxCancion->sig;
				auxCancion->sig = otroAux->sig;
				//Se escribe la informacion de la cancion en el archivo de salida
				fprintf(salida, "%d;%s;%s;%s;%s\n", otroAux->puntaje, otroAux->nombre, segundosTiempo(otroAux->duracion), otroAux->artista, otroAux->genero);
				//Se actualiza el nuevo primer elemento de la lista de ids de generos preferidos
				listaPreferencias = listaPreferencias->sig;
				auxPref->sig = NULL;
				//Se agrega el id del genero acual al final de la lista de preferencias
				listaPreferencias = agregarFinalDato(listaPreferencias, auxPref);
				//Se actualiza la duracion actual de la playlist
				duracionActual += otroAux->duracion;
				otroAux->sig = NULL;
				//Se agrega la cancion agregada al final de la lista de canciones ya agregadas
				cancionesAgregadas = agregarFinalNodo(cancionesAgregadas, otroAux);
			}
			//Caso en donde no se encontro una cancion que cumpla con el genero buscado
			else if (auxCancion->sig == NULL){
				//Se actualiza al nuevo primer elemento de la lista de preferencias
				listaPreferencias = listaPreferencias->sig;
				free(auxPref);
			}
		}
	}

	//En caso de que se supero el limite de tiempo, se escribe por cuando tiempo se excedio la ultima cancion agregada
	if (duracionActual > duracionPlaylist){
		fprintf(salida, "%s\n", segundosTiempo((duracionActual-duracionPlaylist)));
	}
	//Se cierra el archivo de salida
	fclose(salida);

	return;
}



int main(int argc, char const *argv[]){

	//Creamos una lista enlazada con las canciones y la informacion contenida en el archivo de canciones
	nodo *listaCanciones = leerCanciones(argv[1]);
	//Se comprueba que no haya existido un error al leer el archivo de entrada
	if(listaCanciones == NULL){
		printf("El archivo de entrada que contiene las canciones no existe\n");
		return 0;
	}
	
	//Se agrega la informacion del artista a cada cancion en la lista enlazada
	listaCanciones = leerArtistas(argv[2], listaCanciones);
	//Se comprueba que no haya existido un error al leer el archivo de entrada
	if(listaCanciones == NULL){
		printf("El archivo de entrada que contiene los artistas no existe\n");
		return 0;
	}
	
	//Se agrega la informacion del genero de cada cancion en la lista enlazada
	listaCanciones = leerGeneros(argv[3], listaCanciones);
	//Se comprueba que no haya existido un error al leer el archivo de entrada
	if(listaCanciones == NULL){
		printf("El archivo de entrada que contiene los generos no existe\n");
		return 0;
	}
	
	//Se ordena la lista de canciones
	nodo *listaCancionesOrdenada = ordenarCanciones(listaCanciones);
	
	//Se genera el archivo de salida con las canciones ordenadas
	generarSalidaCanciones(listaCancionesOrdenada);
	
	int duracionPlaylist;
	//Se lee el archivo de preferencias para la playlist y se almacenan los ids de los generos en una lista
	nodoDato *listaPreferencias = leerPreferencias(argv[4], &duracionPlaylist);
	//Se comprueba que no haya existido un error al leer el archivo de entrada
	if(listaPreferencias == NULL){
		printf("El archivo de entrada que contiene las preferencias para la playlist no existe\n");
		return 0;
	}
	
	//Se genera el archivo de salida con las canciones que componen la playlist
	crearPlaylist(listaCancionesOrdenada, listaPreferencias, duracionPlaylist);
	

	return 0;
}
