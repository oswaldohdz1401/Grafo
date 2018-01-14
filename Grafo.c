#include  "prototipos.h"

void main(){
    //Creamos una lista de tipo GRAFO
    Lista Grafo;
    inicializa(&Grafo);
	crea_grafo(&Grafo);
	dijkstra(&Grafo,0,3);
	//imprimeListaGrafo(Grafo);
	
}
void crea_grafo(Lista *G){
	FILE *archivo;
	char caracter;
	archivo = fopen("prueba.txt","r");
	int n = 0;
	if (archivo == NULL){printf("\nError de apertura del archivo. \n\n");exit(1);}
	else{
	    while(!feof(archivo)){
			caracter = fgetc(archivo);
            if(fgetc(archivo) == ':'){
            	n = caracter;
			}  
        }
        reserva_grafo(G,(int)n-48);
	}
}
void reserva_grafo(Lista *g,int n){
    int i=0,j=0,k=0;
    int cantidadAristas = 0;
    if((n>1)||(n != 0)){
        for(i=0;i<n;i++){
        	Dato nuevoDatoVertice;
    		Vertice *v = (Vertice *)malloc(sizeof(Vertice));
    		
			Lista *aristas = (Lista*)malloc(sizeof(Lista));
			Dato nuevoDatoArista;
			
    		inicializa(aristas);
        	cantidadAristas = saleCantAristasAdyacentes(i);
        	for(j=0;j<cantidadAristas;j++){
        		
        		Arista *A = (Arista*)malloc(sizeof(Arista));
        		setArista(A,j+k);
        		nuevoDatoVertice = (Dato)(A);
        		insertaFinal(aristas,nuevoDatoVertice);
			}
			printf("\n\n");
			nuevoDatoVertice=creaDatoVertice(i,cantidadAristas,(void*)(aristas),v);
			insertaFinal(g, nuevoDatoVertice);
			k=j;
		}
	}	
}
void setArista(Arista * A,int n){
    int destino = 0;
    int peso = 0;
    destino = saleDestino(n);
    peso = salePeso(n);
    creaDatoArista(destino,peso,A);
}
/*----------------------------------------------------------------------------*/
void iniDatoVertice(Vertice *consulta){
	consulta -> distancia = MAX;
	consulta -> visitado = 0;
}
void iniVertices(Lista *A){
	Nodo * aux;
	aux= A->inicio;
	if(esVacia(*A)!=1){
		while(aux!=NULL){
			iniDatoVertice(aux->contenido);
			aux= aux->sig;
		}
	}else{
		 printf("Lista vacia");
	}
}
Dato regresaNodoMejorPeso(Lista A){
	Nodo *aux;
	aux = A.inicio;
	Vertice a_comparar;
	int mejorDistancia = 0;
	int comparador;
	Nodo *pos = A.inicio;
	Dato *mejor;
	while(esVacia(A) != 1 && aux!=NULL){
		a_comparar = (*(Vertice *)(aux->contenido));
		comparador = a_comparar.distancia;
		if(comparador <= mejorDistancia){
			mejorDistancia = comparador;
			mejor = pos->contenido;
			pos = pos->sig;
		}
		aux = aux->sig;
	}
	return (Dato)mejor;
}
void regresarElFinal(Lista *A,Vertice *v){
	Nodo *aux;
	aux = A->fin;
	v = &(*(Vertice*)(aux->contenido));
}
Dato regresaElInicio(Lista *A){
	Dato inicio;
	Nodo *aux;
	aux = A->inicio;
	inicio = (aux->contenido);
	Vertice *consulta = inicio;
	consulta -> distancia = 0;
	return (Dato)inicio;
}
Dato obtenenVerticeYBuscalo(Lista *A,int d){
	Nodo *aux = A->inicio;
	Vertice a;
	while(aux != NULL){
		a = (*(Vertice *)(aux->contenido));
		if (a.id == d){
			a.visitado = 1;
			return aux->contenido;
		}
		aux = aux->sig;
	}
}
/*
void relacion(Lista *caminoCorto, Vertice encontrado , Vertice mejor){
	if(encontrado.distancia + mejor.distancia < mejor->distancia){
		
	}
}*/
int verificaEnGrafo(Lista A,int a, int b){
	int primero = 0;
	int segundo = 0;
	Nodo *aux = A.inicio;
	Dato dComparar;
	Vertice *vComparar;
	while(aux != NULL){
		dComparar = aux->contenido;
		vComparar = &(*(Vertice *)(dComparar)); 
		if(vComparar->id == a){primero = 1;}
		if(vComparar->id == b){segundo = 1;}
		if(primero && segundo){
			return 1;
		}
		aux = aux->sig;
	}
	return 0; 
}
int obtenDistanciaDeAdyacente(Lista A,int d){
	Nodo *aux = A.inicio;
	Vertice a;
	while(aux != NULL){
		a = (*(Vertice *)(aux->contenido));
		if (a.id == d){
			return a.distancia;
		}
		aux = aux->sig;
	}
}
void unionListaAdyacentes(Lista *A,Vertice u){

}
void dijkstra (Lista *A,int a, int b){
	iniVertices(A);
	int i;
	int tam;
	int w = 0;
	
	//
	/*Sacamos de la lista el inicio para recorrer el grafo*/
	Lista caminoCorto;	inicializa(&caminoCorto);
	insertaInicio(&caminoCorto,(Dato)obtenenVerticeYBuscalo(A,a));
	Nodo 	*aux;

	
	/*--Realizando una lista de adyacencias del ultimo vertice--*/
	Lista adyacencia; inicializa(&adyacencia);
	Vertice *ultimo = (Vertice *)malloc(sizeof(Vertice));
	Nodo *AUX;
	/*Aristas que recorrera cada Arista adyacente*/
	Arista 	*a_Recorrer = (Arista *)malloc(sizeof(Vertice));
	
	
	if (verificaEnGrafo(*A,a,b)) {
		/*Hacemos pop del ultimo vertice del camino más corto
		 y lo almacenamos en el ultimo vertice*/
		aux = (caminoCorto.inicio);
		while(aux != NULL){
			/*Regresamos el final del la pila de adyacencias*/
			regresarElFinal(&caminoCorto,ultimo); 
			/*De nuestra lista de adyacencias obtenemos la ultima lista*/
			insertaInicio(&adyacencia,ultimo->listaAristas);
			/*Vamos a recorrer la lista de adyacencias para encontrar el camino más corto*/
			AUX = adyacencia.inicio;
			while(AUX != NULL){
				a_Recorrer = &(*((Arista*)(AUX->contenido)));
				printf("%d]]]\n\n\n",a_Recorrer->visitado);
				
				AUX = AUX -> sig;
			}
			aux = aux->sig;
		}
			/*

			
			
			*/
			
		 
		/*
			if(ultimo->visitado == 0 && ultimo->id != b){
				ultimo->visitado = 1;
				mejor->distancia = MAX;
				while(AUX != NULL && ultimo->id != b){
					a = &(*((Arista*)(AUX->contenido)));
					if(a->visitado == 0 && ultimo->distancia + a->peso < obtenDistanciaDeAdyacente(*A,(int)a->destino)){
						a->visitado = 1;
						if(ultimo->distancia + a->peso < mejor -> distancia){
							obtenenVerticeYBuscalo(*A,a->destino,mejor);
							mejor->distancia = ultimo->distancia + a->peso ;
							mejor -> visitado = 1;
						}
					}
					a->visitado = 1;
					AUX = AUX->sig;
				}
				insertaFinal(caminoCorto,(Dato)(mejor));
			}
			aux = aux->sig;
		 }*/
	}
	imprimeListaGrafo(caminoCorto);	
}
/*-----------------------------------------*/
void imprimeArista(Arista A){
	printf("\tDestino: %d  Peso: %d\n", A.destino,A.peso);
	
}
void imprimeListaVertices(Lista A){
	Arista a;
	Nodo *aux;
	if(esVacia(A)==0){
		aux= A.inicio;
		while(aux!=NULL){
			a =*((Arista*)(aux->contenido));
			imprimeArista(a);
			aux= aux->sig;
		}
	}else{
		 printf("NO existen aristas adayacentes en el VERTICE");
	}
}
void imprimeVertices(Dato consultando){
	Lista vertices;
	Vertice a_imprimir=(*(Vertice *)(consultando));
	imprimeDatoVertice(a_imprimir);
	vertices =   * ((Lista*)a_imprimir.listaAristas);
	imprimeListaVertices(vertices);
}
void imprimeListaGrafo(Lista A){
	Dato  aimprimir;
	Nodo * aux;
	aux= A.inicio;
	if(esVacia(A)!=1){
		while(aux!=NULL){
			aimprimir=(aux->contenido);
			imprimeVertices(aimprimir);
			aux= aux->sig;
		}
	}else{
		 printf("Lista vacia");
	}
}
