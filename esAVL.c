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

	alturaIz = Altura(T->izq);
	alturaDr = Altura(T->der);

	//diferencia de alturas
	if((alturaIz - alturaDr) > 1){
		return 0;
	}

	if(esAVL(T->izq) && esAVL(T->der)){
		return 1;
	}
}