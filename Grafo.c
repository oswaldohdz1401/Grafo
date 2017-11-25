#include  "listas.h"
#include  "lecturaArchivos.h"
void crea_grafo(Lista *G);
void reserva_grafo(Lista *g,int n);
void setArista(Arista * A,int n);
void vertices_ady(Lista G);
void vertice_a_adyacente_b(Lista G);
Dato capturaIdVertice();
void imprimeListaGrafo(Lista A);

main(){
    //Creamos una lista de tipo GRAFO
    Lista Grafo;
    inicializa(&Grafo);
	crea_grafo(&Grafo);
	imprimeListaGrafo(Grafo);
	//vertices_ady(Grafo);
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
/*-----------------------------------------------------------------------------------*/
/*captuda id del vertice*/
Dato capturaIdVertice(){
	int idNode=-1;
	/*te pide Vertice buscado*/
	do{
		fflush(stdin);
		printf("\n\tDame Nodo Buscado");
    	scanf("\t%d",&idNode);	
	}while(idNode<0);
	return (Dato)idNode;
}
/*todas las adyacencias de nodo buscado*/
void vertices_ady(Lista G){
	Dato idNode;
	Nodo node;
	Vertice verticeResult;
	Lista *listaAristas;
	Nodo *nodo;
	Dato arista;
	
	idNode= capturaIdVertice();						//modifique
    node=*(Nodo*)nodos_adyacentes(G,idNode,compara);//modifique 
    verticeResult=*(Vertice*)node.contenido;
    listaAristas=(Lista*)verticeResult.listaAristas;
    nodo =listaAristas->inicio;
    
    while(nodo!=NULL){
 		arista= (nodo->contenido);
    	imprimeDatoArista(arista);
		nodo= nodo->sig;
	}	   
}

/*Adyacencia entre nodo A y Nodo B*/
void vertice_a_adyacente_b(Lista G){
	Dato idNodeA;/*nodo A a comparar*/
	Dato idNodeB;/*nodo B a comparar*/

	Nodo node;
	Vertice verticeResult;
	Lista *listaAristas;
	Nodo *nodo;
	Dato arista;
	
	idNodeA = capturaIdVertice();
	idNodeB = capturaIdVertice();
	node=*(Nodo*)nodos_adyacentes(G,idNodeA,compara);
    verticeResult=*(Vertice*)node.contenido;
    listaAristas=(Lista*)verticeResult.listaAristas;
    nodo =listaAristas->inicio;
    
	 while(nodo!=NULL){
 		arista= (nodo->contenido);
    	/*imprimeDatoArista(arista);*/
    	vertexAdyacentes(arista,idNodeB);
		nodo= nodo->sig;
	}	   
	
}

