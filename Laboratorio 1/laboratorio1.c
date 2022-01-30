#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructura que tendra cada postulante del archivo de entrada
typedef struct Postulante
{
    char nombre[150];
    int peso;
    int calificacion;

} Postulante;

//Funcion que crea un postulante con los argumentos entregados y retorna al postulante creado
Postulante cearPostulante (char nombre[], int peso, int calificacion)
{
	Postulante nuevoPostulante;

	strcpy(nuevoPostulante.nombre, nombre);
	nuevoPostulante.peso = peso;
	nuevoPostulante.calificacion = calificacion;

	return nuevoPostulante;
}

//Funcion encargada de leer el archivo de entrada y generar un arreglo con los postulantes
//Recibe como argumento un el nombre del archivo de entrada, la direccion de memoria del entero donde se guardara la cantidad de postulantes y la direccion de memoria del entero donde se guardara el peso maximo
//Retorna un arreglo de Postulante(struct) con los postulantes del archivo de entrada y actualiza el valor de la cantidad de postulantes y el peso maximo
Postulante* leer (char const* nombre, int *postulantes, int *pesoMax)
{
	FILE *pf;
	//Se abre el archivo en modo lectura
	pf = fopen(nombre, "r");

	//En caso de que el archivo de entrada no exista
	if (pf == NULL)
	{
		Postulante * listaPostulantes = (Postulante*)malloc(sizeof(Postulante)*1);
		listaPostulantes[0].peso = -1;
		return listaPostulantes;
	}

	else
	{
		//Almacena el primer elemento del archivo que corresponde la cantidad de postulantes en la variable postulanes
		fscanf(pf, "%d", &*postulantes);
		//Almacena el segundo elemento del archivo que corresponde peso maximo soportado por la nave en la varible pesoMax
		fscanf(pf, "%d", &*pesoMax);

		//En caso de que la cantidad de postulantes o el peso maximo no sea valido
		if (*postulantes <= 0 || *pesoMax <= 0)
		{
			Postulante * listaPostulantes = (Postulante*)malloc(sizeof(Postulante)*1);
			listaPostulantes[0].peso = -2;
			return listaPostulantes;
		}
		

		//Se crea una lista de postulantes para almacenar los postulantes almacenados en el archivo de entrada
		Postulante * listaPostulantes = (Postulante*)malloc(sizeof(Postulante)*(*postulantes));

		int i = 0;
		//Ciclo para recorrer el archivo hasta llegar al final de este
		while(feof(pf) == 0)
		{
			//Se crea un nuevo postulante
			Postulante actual;

			//Se leen y almacenan los datos del postulante
			fscanf(pf, "%s", actual.nombre);
			fscanf(pf, "%d", &actual.peso);
			fscanf(pf, "%d", &actual.calificacion);

			//En caso de que se ingrese un valor invalido en 
			if (actual.peso <= 0 || actual.calificacion <= 0)
			{
				Postulante * listaPostulantes = (Postulante*)malloc(sizeof(Postulante)*1);
				listaPostulantes[0].peso = -2;
				return listaPostulantes;
			}
			//Se agrega el postulante a la lista de postulantes
			listaPostulantes[i] = actual;
			i += 1;
		}

		//Se cierra el archivo de entrada
		fclose(pf);

		//Se retorna la lista de postulantes
		return listaPostulantes;
	}
	
}

//Funcion que crea un nombre con los postulantes que componen una combinacion
//Recibe como argumentos la lista de posiciones, el largo de la combinacion actual, la lista de postulantes, el peso acumulado y la calificacion acumulada
//Retorna un postulante que representa la combinacion actual
Postulante crearSolucion (int* posiciones, int largo, Postulante* postulantes, int peso, int calificacion)
{
	//Se crea una variable (char) auxiliar que contendra el nombre final de la solucion (union de todos los postulantes)
	char auxiliar[110];
	//Se iguala la variable variable auxiliar a un string vacio para que no se altere el nombre
	strcpy(auxiliar,"");

	//Ciclo que recorre los elementos del arreglo posiciones
	for(int b = 0; b < largo; b++)
	{
		//Une el nombre acumulado en la variable auxiliar con el nombre del postulante en la posicion actual
		strcat(auxiliar, postulantes[posiciones[b]].nombre);

		//Si es que queda otro elemento a agregar se agregara una coma al final del stirng para separar el nombre de los postulantes
		if (b+1 < largo)
		{
			strcat(auxiliar, ", ");
		}	
	}
	
	Postulante solucion = cearPostulante(auxiliar, peso, calificacion);
	
	free(auxiliar);
	return solucion;
}

//Funcion que genera una nueva lista de soluciones con la solucion agregada al final de esta
//Recibe como argumentos una lista de soluciones, el largo de la lista de soluciones y la solucion a agregar
//Retorna un arreglo de Postulante con los elementos antiguos el el nuevo al final
Postulante* agregarSolucion (Postulante * listaSoluciones, int *largoLista, Postulante solucionAgregar) 
{
    Postulante * nuevaLista = (Postulante*)malloc(sizeof(Postulante)*((*largoLista)+1));  //Se crea una nueva lista con el tamanio nuevo

    //Copiamos los elementos de la lista antigua a la nueva
    for (int i = 0; i < *largoLista; i++)  //Ciclo para recorrer los elementos de la lista
    {
        strcpy(nuevaLista[i].nombre, listaSoluciones[i].nombre);
        nuevaLista[i].peso = listaSoluciones[i].peso;
        nuevaLista[i].calificacion = listaSoluciones[i].calificacion;
    }

    //Ahora copiamos la nueva solucion al final de la lista
	strcpy(nuevaLista[*largoLista].nombre, solucionAgregar.nombre);
	nuevaLista[*largoLista].peso = solucionAgregar.peso;
	nuevaLista[*largoLista].calificacion = solucionAgregar.calificacion;

    free(listaSoluciones);  //Liberamos la memoria utilizada por la antigua lista
    *largoLista = *largoLista + 1;  //Actualizamos el largo de la lista

    return nuevaLista;  //Retornamos la nueva lista 
}


//Funcion que toma una lista de postulantes y realiza todas las posibles combinaciones de sus elementos
//Recibe como argumentos: El arreglo donde se almacenaran las posiciones que contienen la combinacion; el valor del siguiente elemento a agregar en la combinacion; la cantidad de elementos que contiene la combinacion actualmente;
//                        la cantidad de elementos que debe tener la combinacion; el arreglo de postulantes; el largo del arreglo de postulantes; la suma del peso de los postulantes que comforman la combinacion actual;
//                        la suma de la calificacion de los postulantes que comforman la combinacion actual; el peso maximo de la nave; el arreglo donde se guardaran las soluciones y el largo del arreglo de soluciones
//No retorna nada, pero si agrega las soluciones que cumplen el requisito de peso a la lista de soluciones, ademas actualiza el valor de la cantidad de soluciones que hay en el arreglo de soluciones
Postulante* combinacion (int* posiciones, int indice, int longitud, int cantElementos, Postulante* listaPostulantes, int postulantes, int peso, int calificacion, int capacidad, Postulante* soluciones, int *cantSoluciones)
{
	//Caso base, si la longitud de la combinacion es la deseada
	if (longitud == cantElementos) 
	{		
		//Se comprueba que la solucion generada cumpla la condicion de no superar el peso maximo de la nave
		if (peso <= capacidad)
		{
			Postulante actual = crearSolucion(posiciones, longitud, listaPostulantes, peso, calificacion);

			//Agregamos las nueva solución a la lista de soluciones
			soluciones = agregarSolucion (soluciones, cantSoluciones, actual);

		}
	}

	//Caso general
	else 
	{
		//Ciclo para incrementar la nueva posicion que se agregara al arreglo de posiciones
		for (int i = indice; i < postulantes; i++)
		{
			//Se guarda la nueva posicion de la combinacion
			posiciones[indice] = i;
			//Llamado recursivo, el indice aumenta para indicar la siguiente posicion de la combinacion, se suma 1 a la longitud de la combinacion actual, se suma el peso del nuevo postulante de la combinacion al argumento peso, 
			//se suma la calificacion del nuevo postulante de la combinacion al argumento calificacion y el resto de los argumentos se mantienen igual.
			soluciones = combinacion (posiciones,i+1,longitud+1,cantElementos, listaPostulantes, postulantes, peso+listaPostulantes[i].peso, calificacion+listaPostulantes[i].calificacion, capacidad, soluciones, cantSoluciones);
		}
	}
	return soluciones;
}

//Funcion que se encarga de intercambiar la posicion de dos elementos dentro de un arreglo de Postulante
void swap(Postulante *xp, Postulante *yp) 
{ 
    Postulante temp = *xp; 
    *xp = *yp; 
    *yp = temp; 

	return;
} 
  
// Funcion que implementa el metodo de oredenamiento bubblesort sobre una lista de postulantes (struct) basados en su calificacion
void bubbleSort(Postulante arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)   
   {    
       for (j = 0; j < n-i-1; j++)
	   {  
           if (arr[j].calificacion < arr[j+1].calificacion) 
		   {
			   swap(&arr[j], &arr[j+1]);
		   }
               
	   }
   }
   return;
} 

//Funcion que genera el archivo de texto de salida
//Recibe como argumentos el arreglo con las soluciones y la cantidad de elementos que hay en el
//Gerera el archivo de texto y no retorna nada
void generarSalida (Postulante* listaSoluciones, int cantSoluciones)
{
	FILE* salida;
	//Se abre el archivo "tripulacion.out" en modo escritura (lo creara si no existe o lo remplazara si existe)
	salida = fopen ("tripulacion.out", "w");

	//Ciclo para escribir cada solucion de la lista de soluciones en una linea
	for(int i = 0; i < cantSoluciones; i++)
	{ 
		
		//Se escribe la solucion 
		fprintf(salida, "%s, %d, %d\n", listaSoluciones[i].nombre, listaSoluciones[i].peso, listaSoluciones[i].calificacion);
	}

	//Se cierra el archivo de salida
	fclose(salida);

	return;
}


int main(int argc, char const *argv[])
{
	//Se define las variables para almacenar la cantidad de postulantes del archivo y el peso maximo de la nave
	int postulantes, pesoMax;
	
	//Se lee el archivo de entrada que retorna una lista de postulantes que sera almacenada en la variable nave
	Postulante* nave = leer (argv[1], &postulantes, &pesoMax);

	if(nave[0].peso == -1)
	{
		printf("El archivo de entrada no existe\n");
		return 0;
	}

	if(nave[0].peso == -2)
	{
		printf("Error en el formato del archivo de entrada\n");
		return 0;
	}
	
	//Se reserva memoria para un arreglo de enteros que contendra las posiciones de la combinacion de postulantes
	int* posiciones = (int *)malloc(sizeof(int)*(postulantes));

	//Se inicializa cantSoluciones en cero, ya que aun no existen soluciones
	int cantSoluciones = 0;
	//Se crear una lista para almacenar las soluciones del largo igual a la cantidad de soluciones actuales
	Postulante * soluciones = (Postulante *)malloc(sizeof(Postulante)*cantSoluciones);

	//Ciclo que lleva la cuenta de cuantos elementos debe tener la combinacion del ciclo correspondiente
    for (int cantElementos = 1; cantElementos <= postulantes; cantElementos++)
    {
		
		//Ciclo para recorrer los elementos de una lista de postulantes, la variable i sirve para elegir el pivote de la combinatoria
        for (int i = 0; i < postulantes; i++)
		{
			
			//Se almacena el valor del "pivote" como primer elemento del arreglo de posiciones
			posiciones[0] = i;

			//Se llama la funcion para generar las combinaciones de postulantes
			soluciones = combinacion(posiciones, i+1, 1, cantElementos, nave, postulantes, nave[i].peso, nave[i].calificacion, pesoMax, soluciones, &cantSoluciones);
		}
    }
	
	//Se ordena de mayor calificacion a menor las soluciones contenidas en la lista de soluciones
	bubbleSort(soluciones, cantSoluciones);
	
	generarSalida(soluciones, cantSoluciones);
	
	//Se libera la memoria utilizada por los arreglos
	free(posiciones);
	free(soluciones);
	free(nave);

	return 0;
}