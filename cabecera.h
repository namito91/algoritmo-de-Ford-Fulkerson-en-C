#ifndef CABECERA_H_
#define CABECERA_H_
#endif /* CABECERA_H_ */

#include <stdio.h>
#include <stdlib.h>
#define V 6
#define true 1
#define false 0
#define semicaminos_posibles 4
#include <limits.h>
#include <string.h>

// macro que compara dos numeros y retorna el menor
//#define min(x,y)  (( x ) < ( y ) ) ? ( x ) : ( y )
#define min(x,y)  (( x ) < ( y ) ) ? ( x ) : ( ( x ) ==  ( y ) ) ? ( x ) : (y)

// Se armaran los semicaminos de s a T usando a los nodos
//como indices
// en el pseudocodigo lo llamamos p
int semicamino [ V ];


// Definimos la red
int red [ V ][ V ] = { {0,4,6,0,0,0},
                       {0,0,0,3,5,0},
                       {0,0,0,0,6,0},
                       {0,0,9,0,0,5},
                       {0,0,0,0,0,4},
                       {0,0,0,0,0,0} };

int flujos [ V ][ V ] = { {0,4,6,0,0,0},
                          {0,0,0,3,5,0},
                          {0,0,0,0,6,0},
                          {0,0,9,0,0,5},
                          {0,0,0,0,0,4},
                          {0,0,0,0,0,0} };

int Grafo_aux [ V ][ V ] = { {0,4,6,0,0,0},
                             {0,0,0,3,5,0},
                             {0,0,0,0,6,0},
                             {0,0,9,0,0,5},
                             {0,0,0,0,0,4},
                             {0,0,0,0,0,0} };
                                            // 0 1 2 3 4 5
int flujo_circulando_en_arista [ V ][ V ] = { {0,0,0,0,0,0}, // 0
                          	  	  	 	 	  {0,0,0,0,0,0}, // 1
											  {0,0,0,0,0,0}, // 2
											  {0,0,0,0,0,0}, // 3
											  {0,0,0,0,0,0}, // 4
											  {0,0,0,0,0,0}};// 5

int flujo_disponible_en_arista [ V ][ V ] = { {0,0,0,0,0,0},
                          	  	  	 	 	  {0,0,0,0,0,0},
											  {0,0,0,0,0,0},
											  {0,0,0,0,0,0},
											  {0,0,0,0,0,0},
											  {0,0,0,0,0,0}};

int arista_usada [ V ][ V ] = { {0,0,0,0,0,0},
                          	  	{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0}};

int flujo_total [ V ][ V ] =  { {0,0,0,0,0,0},
                          	  	{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0},
								{0,0,0,0,0,0}};


typedef struct nodo{

    int dato;
    struct nodo* siguiente;

}nodo;


struct nodo* frente = NULL;
struct nodo* ultimo = NULL;
int contador = 0;
static int contador2 = 0;
int control = 0;
//int aristas [V];


void encola (nodo **frente,nodo **ultimo,int var ){

  struct nodo* nodo_nuevo = (struct nodo*)malloc(sizeof(struct nodo));
  //struct nodo* nodo_anterior = (struct nodo*)malloc(sizeof(struct nodo));

  if(nodo_nuevo == NULL){
    printf("no hay espacio en el sistema \n");
    return;
  }

  if (*frente == NULL ){

	  *frente = nodo_nuevo;
	  *ultimo = nodo_nuevo;
	  (*frente)->siguiente = NULL;
	  nodo_nuevo->dato = var;

	  return;
  }

  //(*ultimo)->siguiente = nodo_nuevo;
  nodo_nuevo->dato = var;
  nodo_nuevo->siguiente = NULL;
  (*ultimo)->siguiente = nodo_nuevo;
  *ultimo = nodo_nuevo;
  //printf("dato : %d", nuevo_nodo->dato);
};


int desencola (nodo** tope){

    if(*tope == NULL){
        printf("la cola esta vacia \n");
        return -1;
    }

    struct nodo* temporal = *tope;
    *tope = temporal->siguiente;
    int valor = temporal->dato;
   // printf("nodo eliminado : %d\n", valor);
    free(temporal);
    temporal = NULL;

    return valor;
};


int esta_vacia ( nodo** comienzo ){

    if ( *comienzo == NULL ){

        return 1;
    }else{
        return 0;
    }
};


void imprimir_cola (nodo* frente ){

    if (frente == NULL) {
    	printf("no hay elementos para imprimir \n");
    }

    int i = 1;
    struct nodo* temporal = frente;
    while(temporal != NULL){

      //  printf("elemento %d de la cola : %d \n",i, temporal->dato);
        temporal = temporal->siguiente;
        i++;
    }
};



/* Analiza las aristas salientes de cada vertice, en caso de tener dos aristas salientes (el vertice),
 elimina una,para no repetir el mismo semicamino.
 En caso de quedarse con una sola arista saliente,
 solo se vuelve a usar, si esta unica arista puede formar parte de un semicamino distinto. */

void analiza_vertice ( int semicamino [V] , int var , int i ,int aristas[V] , int sum ) {

            int fila = semicamino [i-1];
            int columna = semicamino[i];
            //int temp = i;
            int j = i;

            if ( aristas[fila] == 2  ){

                int tmp = Grafo_aux [fila][columna];
                Grafo_aux[fila][columna] = 0;
               // *(aristas + 1) -= 1;

                /*
                int arreglo_tmp[3];

                arreglo_tmp[0] = fila;
                arreglo_tmp[1] = columna;
                arreglo_tmp[2] = tmp;
                */

                printf("***arista eliminada : fila [%d] columna [%d] valor eliminado en la matriz : %d \n ", fila,columna,tmp );
                return;
                //aristas[i] -= 1;
            }
            else {

                if ( sum == 5 ) return;
                i--;
                analiza_vertice ( semicamino, var, i,aristas,sum );
            }
};


    /* Devuelve true si hay un camino desde la fuente de ’s ’
    bajando a ’t ’ en
    red auxiliar . éTambin se llena de los semicamino [] para
    almacenar el camino */

void busqueda_camino ( int red_aux [ V ][ V ] , int s , int t , int semicamino [V] , int **ptr_semicamino ) {

    // Crear vector visitado y marcar todos los évrtices como
    // no visitados

    int visitado [ V ];
    int padres [ V ];
    int temp [V];
    int aristas [V];
    memset ( visitado , 0 , sizeof ( visitado ) );
    memset ( padres , 0 , sizeof ( padres ) );
    memset ( temp , 0 , sizeof ( temp ) );
    memset ( aristas , 0 , sizeof ( aristas ) );

    // óCreacin de una cola , évrtice fuente encola y marcar évrtices fuente como visitado

    encola( &frente , &ultimo, s );
    imprimir_cola(frente);
    visitado[s] = 1;
    padres[s] = 0;
    //printf (" valor de s : %d \n", s );
    //var++;


    // INICIALIZA Y ACTUALIZA  LOS VALORES DE LAS ARISTAS SALIENTES DE CADA VERTICE EN LA MATRIZ ,
    //SI EL VERTICE TIENE DOS ARISTAS SALIENTES,
    //ENTONCES ELIMINA UNA SOLA,NO MAS QUE ESO,
    //POR QUE MANTENER EL ARREGLO "ARISTAS" CON VALORES EN "1" AYUDA A LOS PROPOSITOS GLOBALES DEL PROGRAMA.
        for ( int i = 0; i < V ; i++ ){
        for ( int j = 0; j < V ; j++ ){

            if ( red_aux [i][j] != 0 )
                aristas [i] = contador+=1 ;

        }
        contador = 0;
        }

    printf("aristas salientes de cada vertice \n");
    for ( int i = 0; i < V ; i++ ){

        printf("%d \t", aristas [i] );
    }

    printf ( "\n" );

    // Se recorre red_aux para encontrar las adyacencias y los semicaminos, ( algoritmo BFS )
    while ( esta_vacia(&frente) != 1 ){

    // extraemos el nodo u de la cola Q y exploramos todos sus nodos adyacentes
    //s = proximo elemento en la cola a ser analizado
    s = desencola(&frente);
   // printf("proximo nodo a analizar : %d \n", s);

        for ( int i = 0;i < V ; i++ ){
            if ( red_aux[s][i] != 0 ){
                if ( visitado[i] == 0 ){

                    visitado[i] = 1;
                    padres[i] = s;
                   // printf("***nuevo nodo en la cola : %d  \n", i);
                    encola(&frente,&ultimo,i);
                    imprimir_cola(frente);
                }
            }
        }
    }

    printf("\n");
    /*
    printf("nodos padres \n");
    for (int i = 0; i < V ; i++)
            printf ( "elemento %d :  %d \n",i, padres[i] );
*/
    contador = 0;
    contador2 = 0;
    for (int i = t , j = 0; i != NULL ; i = padres[i],j++ ){

        if ( i == 0  ){
            contador++;
        }

        if ( contador == 2 )
            continue;
            else{
                temp [j] = i;
                contador2++;
}
}

/*
    for (int i = 0; i < sizeof (contador2)  ; i++)
            printf ( "elemento %d :  %d \n",i, temp [i] );
*/
    printf("contador : %ld \n ",sizeof (contador2) );
    for ( int i = 0, j = contador2  ; j >= 0 ;i++,j-- ){
    	semicamino[i] = temp[j];
    	ptr_semicamino[control][i] = temp[j]; // guardo el semicamino en un puntero de dos dimensiones ( arreglo )
    }


    printf("\n");
    printf("semicamino \n");
    for (int i = 0; i <= contador2 ; i++){
            printf ( "vertice %d :  %d \n",i, semicamino[i] );
           // printf ( "vertice %d :  %d \n",i, ptr_semicamino[control][i] );
    }

    // BUSCA EL ULTIMO VERTICE QUE HIZO CONTACTO CON LA FUENTE PARA DESCARTARLO ( PONE EL VALOR EN 0 EN LA MATRIZ, PARA NO VOLVER A USAR LA MISMA ARISTA Y NO REPETIR EL MISMO CAMINO  ) ,
    // Y ASI BUSCAR OTRO SEMICAMINO POSIBLE

     // bucle controla las aristas
    int sum = 0;
    for ( int i = 0; i < V ; i++ )
        sum += aristas [i];


   // int* arista_eliminada;
    for (int i = 0 ; i < V; i++){

        if ( semicamino[i] == t )
   //  int arista_eliminada;
            analiza_vertice( semicamino,contador2,i, aristas ,sum );
    }

    // se imprime el estado de la matriz alternativa.
    printf("\n");
    printf ( "estado de la matriz alternativa : \n" );
      for ( int i = 0; i < V ; i++ ){
        for ( int j = 0; j < V ; j++ ){
            printf("%d \t", Grafo_aux[i][j] );
        }
    printf("\n");
    }


    if ( sum != 5 ){ // variable sum

    	control += 1;
        busqueda_camino( Grafo_aux, 0 , 5 , semicamino , ptr_semicamino ); // llamada busca otro semicamino , para este grafo

    }else {

     	// cuantos son los semicaminos posibles y no terminar en un bucle infinito( viendo el grafo , es mi pecado en este programa )
           printf ( "no quedan mas caminos por recorrer \n" );
           return;
    }
}



// Retorna el maximo flujo de s a t en el grafico dado
void ford_Fulkerson ( int red [ V ][ V ] , int s , int t ) {

	int filas = 10;
	int columnas = 10;
	// inicia puntero dinamico de dos dimensiones ,para guardar los semicaminos que se iran hallando
	int** ptr_semicamino = (int**) malloc( filas * sizeof( int* ) );
	for (int i = 0; i < filas; i++) {ptr_semicamino [i] = (int *) malloc( columnas * sizeof(int) ); };

	// esta funcion se encarga de buscar todos los semicaminos posibles de la red y
	// los guarda en nuestro puntero de dos dimensiones
	busqueda_camino( Grafo_aux, 0 , 5 , semicamino , ptr_semicamino );

	// obtengo el largo de los cuatro semicaminos, producidos por la funcion anterior
	int largo[semicaminos_posibles] = {0,0,0,0} ;
	int fila = 0;
	for ( int i = 0;  i < semicaminos_posibles ; i++ ) {
		int j = 0;
		largo[i] += 1;
		while (  ptr_semicamino[i][j+1] != 0  ){
			largo[fila] += 1;
			j++;
		}
		fila += 1;
	}
	/* imprime el largo de cada semicamino
	for (int var = 0; var < sizeof (largo) / sizeof (int) ; ++var) {
		printf( " largos : %d \t ", largo[var] );
	}
*/
	// muestro los semicaminos obtenidos
	printf ( "semicaminos : \n" );
	for ( int i = 0; i < semicaminos_posibles ; i ++  ){
		printf ( " semicamino %d \n", i + 1 );
		for ( int j = 0; j < largo[i] ; j ++  ){
			if ( ptr_semicamino[i][j] == 0 && j != 0 ) continue;
			printf ( " %d \t " , ptr_semicamino[i][j]  );
		}
		printf ("\n" );
	}

	// creo un arreglo temporal de dos dimensiones,
	// para guardar los semicaminos obtenidos
	// y poder trabajar con ellos
	int tamanio_semicamino = 7;
	int vertice[ semicaminos_posibles ][ tamanio_semicamino ] ;
	// semicamino 1
	fila = 0;
	// lleno un arreglo con un semicamino, (contenido dentro del puntero de dos dimensiones)
	for (  ;fila < semicaminos_posibles ;  ) {
		int var2 = 0;
		printf( "arreglo temporal %d : ", fila );
		while (  var2 < largo[fila]  ){
			vertice[fila][var2] = ptr_semicamino[ fila ][var2] ;
			printf( "%d \t    " , vertice[fila] [var2]);
			var2 += 1;
		}
	fila += 1;
	printf("\n");
	}

// -------------------------------------------------------------------------------------------------

	// Algoritmo para establecer los flujos de cada camino, y que no se intercruzen.
	// marco las aristas que ya fueron usadas, y su flujo disponible.
	// Para no producir un cuello de botella,el nuevo camino solo va a poder usar
	// el flujo disponible restante ( de la capacidad usada por otro camino anterior )
    //int valor_minimo = 0;
	int valores_minimos [ semicaminos_posibles ] = { 0,0,0,0 } ;
    fila = 0;
    int columna = 0 ;

	for ( ; fila < semicaminos_posibles ; fila++ ){
	    columna = 0 ;
		//Sint temp = 0;
		int valor_anterior;

		// si la arista ya fue usada por otro semicamino,se ajustan los valores de flujo
		// y se toma en cuenta el flujo que ya esta circulando en una misma arista,
		// para darle al nuevo semicamino,solo el flujo restante del ya usado por el
		// primer semicamino,para no exceder la capacidad de flujo de una arista.
		// se trabaja por defecto sobre un semicamino de longitud 3,
		//

		// si alguna de las aristas ya fue usada, darle a to,do el camino,
		// el valor de flujo disponile de la arista ya usada.
			// 1


		// busco el semicamino de longitud 6 , sino,
		// trabajo con los tres semicaminos de longitud 4
		if ( largo[fila ] > 4 ){
			// arista 1
			if ( arista_usada[ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] == 1 ) {

						if ( flujo_disponible_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] == 0){
							printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
							continue;
						}

						valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]];
						int temp = valores_minimos[fila];

						flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
						flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
						flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
						flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

						arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
						arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

						flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
						    flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
							flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
							flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
							flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
							flujos [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
							flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

						continue;
					}

					printf("\n");

					//arista 2
					if ( arista_usada[ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] == 1 ) {

						if ( flujo_disponible_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] == 0){
							 printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
							 continue;
						}

						valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]];
						int temp = valores_minimos[fila];

						flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
						flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
						flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
						flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

						arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
						arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

						flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
							flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
							flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
							flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
							flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
							flujos [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
							flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

						continue;
					}

					printf("\n");

					// arista 3
					if ( arista_usada[ vertice[fila][ columna + 2 ]][ vertice[fila][ columna + 3 ]] == 1 ) {

						if ( flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] == 0){
							 printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
							 continue;
						}

						valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]];
						int temp = valores_minimos[fila];

						flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
						// flujo inverso ***
						flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna] ] = -temp ;
						flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
						flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

						flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
						flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

						arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
						arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

						flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
							flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
							flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
							flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
							flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
						flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
							flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
							flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
						printf(" flujo circulando en arista (%d,%d) : %d  \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna ],vertice[fila][columna+1]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
						printf( " flujo disponible en arista (%d,%d) : %d \n ",
							vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
							flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

						continue;
					}

					// arista 4
					if ( arista_usada[ vertice[fila][ columna + 2 ]][ vertice[fila][ columna + 3 ]] == 1 ) {

					if ( flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] == 0){
						printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
						continue;
					}

					valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]];
					int temp = valores_minimos[fila];

					flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
					// flujo inverso ***
					flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna] ] = -temp ;
					flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

					flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
					flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

					flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
					flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

					arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
					arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

					flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
						flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
						flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
					flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
						flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
						flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
					flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
						flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
						flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

					printf(" flujo circulando en arista (%d,%d) : %d  \n ",
						vertice[fila][ columna ],vertice[fila][columna+1]  ,
						flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
					printf(" flujo circulando en arista (%d,%d) : %d  \n ",
						vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
						flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
					printf(" flujo circulando en arista (%d,%d) : %d  \n ",
						vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
						flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
					printf( " flujo disponible en arista (%d,%d) : %d \n ",
						vertice[fila][ columna ],vertice[fila][columna+1]  ,
						flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
					printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
					printf( " flujo disponible en arista (%d,%d) : %d \n ",
						vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
						flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

					continue;
					}


					printf("\n");

								// si la arista no fue usada,usar el valor minimo de flujo del semicamino,
								//se busca el valor de flujo minimo en dos aristas adyacentes
								valores_minimos[fila] = min ( flujos [ vertice[fila][columna] ][vertice[fila][columna+1] ],
								flujos [ vertice[fila][columna+1] ][vertice[fila][columna+2] ]);

								// guardo la cantidad de flujo circulando en dos aristas,(valor de flujo minimo obtenido entre ellas dos)
								// y en ambas, las registro como usadas,por que ya contienen flujo circulando
								// y para controlar si la misma arista vuelve a ser usada por otro semicamino
								flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] =
									valores_minimos[fila] ;
								flujo_total	[ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] += valores_minimos[fila] ;
								arista_usada[ vertice[fila][ columna ] ][ vertice[fila][ columna + 1 ] ] = 1;
								//arista siguiente a la anterior
								flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]  =
									valores_minimos[fila] ;
								flujo_total	[ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ] += valores_minimos[fila] ;
								arista_usada[ vertice[fila][ columna + 1 ] ][ vertice[fila][ columna + 2 ] ] = 1;

								printf ( "arista ya usada : (%d,%d ) \n ",vertice[fila][ columna ] , vertice[fila][ columna + 1 ]);
								printf ( "arista ya usada : (%d,%d ) \n ",vertice[fila][ columna+1 ],vertice[fila][columna+2]);

							    // actualizo el flujo disponible en dos aristas(capacidad),restandole el nuevo flujo que esta circulando
								flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ]  =
									flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] - valores_minimos[fila] ;

								flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] =
										flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] - valores_minimos[fila] ;

								//arista siguiente a la anterior
								flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]  =
									flujos [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ] - valores_minimos[fila] ;

								// se imprimen los flujos circulando en dos aristas,y el flujo disponible de cada una
								printf(" flujo circulando en arista (%d,%d) : %d  \n ",
									vertice[fila][ columna ],vertice[fila][columna+1]  ,
									flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
								printf(" flujo circulando en arista (%d,%d) : %d \n ",
									vertice[fila][ columna + 1 ],vertice[fila][ columna + 2 ]  ,
									flujo_circulando_en_arista [ vertice[fila][ columna + 1 ] ][ vertice[fila][ columna + 2 ] ]);
								printf( " flujo disponible en arista (%d,%d) : %d \n ",
									vertice[fila][ columna ],vertice[fila][columna+1]  ,
									flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]] );
								printf( " flujo disponible en arista (%d,%d) : %d \n ",
									vertice[fila][columna +1],vertice[fila][columna+2]  ,
									flujo_disponible_en_arista [vertice[fila][columna+1]][vertice[fila][columna+2]] );

								valor_anterior = valores_minimos[fila];
										// temp++;
								//	}

								// se guarda el valor de flujo de la tercer arista siguiente
								int temp2 = min ( flujos [ vertice[fila][columna+1] ][vertice[fila][columna+2] ],
									flujos [ vertice[fila][columna+2] ][vertice [fila][columna+3] ]) ;
								// se compara el valor minimo actual con el valor de flujo de la tercer arista

								if ( valor_anterior > temp2   )  {
									valores_minimos[fila] = temp2;

								//	arista_usada[ largo[control] ][i] = 1 ;
								//printf("valores minimos semicamino 1 %d : %d \n",control, valores_minimos[control]);
								flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = valores_minimos[fila];
								flujo_total	[ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] += valores_minimos[fila] ;
								flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = valores_minimos[fila];
								flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += valores_minimos[fila];
								flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
								flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += valores_minimos[fila];

								flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] =
									flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ] -
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
								arista_usada[ vertice[fila][ columna + 2 ] ][ vertice[fila][ columna + 3 ] ] = 1;
								printf( " flujo circulando en primer arista : %d \n " ,
									flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] );
									//printf(" flujo disponible en tercer arista : %d \n " ,
									//flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

								printf( " flujo circulando en segunda arista : %d \n " ,
									flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] );
								//	printf(" flujo disponible en tercer arista : %d \n " ,
								//	flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

								printf( " flujo circulando en tercer arista : %d \n " ,
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
									printf(" flujo disponible en tercer arista : %d \n " ,
									flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

									}


								else{

										flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
										flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
										flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] =
										flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ] -
										flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
										arista_usada[ vertice[fila][ columna + 2 ] ][ vertice[fila][ columna + 3 ] ] = 1;

										printf( " flujo circulando en tercer arista : %d \n " ,
										flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
										printf(" flujo disponible en tercer arista : %d \n " ,
										flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

									}

								// si el semicamino es mayor a 3 de longitud, entonces darle otro tratamiento
								// if ( largo[fila] > 3  ){

									// si la arista no fue usada,usar el valor minimo de flujo del semicamino,
									//se busca el valor de flujo minimo en dos aristas adyacentes
									valores_minimos[fila] = min ( flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ],
									flujos [ vertice[fila][columna+3] ][vertice[fila][columna+4] ]);

									// aristas (3,2) , (2,4)
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
									flujo_circulando_en_arista [vertice[fila][columna+3]][ vertice[fila][columna+4] ] = valores_minimos[fila];

									flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += valores_minimos[fila];


									flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] =
									flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ] -
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
									arista_usada[ vertice[fila][ columna + 2 ] ][ vertice[fila][ columna + 3 ] ] = 1;

									printf( " flujo circulando en cuarta arista : %d \n " ,
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
									printf(" flujo disponible en cuarta arista : %d \n " ,
									flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );


									// quinta arista
									valores_minimos[fila] = min ( flujos [ vertice[fila][columna+3] ][vertice[fila][columna+4] ],
									flujos [ vertice[fila][columna+4] ][vertice[fila][columna+5 ] ]);


									// aristas (2,4) , (4,5)
									flujo_circulando_en_arista [vertice[fila][columna+3]][ vertice[fila][columna+4] ] = valores_minimos[fila];
									flujo_circulando_en_arista [vertice[fila][columna+4 ]][ vertice[fila][columna+5] ] = valores_minimos[fila];

									flujo_total [vertice[fila][columna+4]][ vertice[fila][columna+5] ] += valores_minimos[fila];

									flujo_disponible_en_arista [vertice[fila][columna+4]][ vertice[fila][columna+5] ] =
								    flujos [ vertice[fila][columna+4] ][vertice[fila][columna+5] ] -
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
									arista_usada[ vertice[fila][ columna + 3 ] ][ vertice[fila][ columna + 4 ] ] = 1;
									arista_usada[ vertice[fila][ columna + 4 ] ][ vertice[fila][ columna + 5 ] ] = 1;
									printf( " flujo circulando en cuarta arista : %d \n " ,
									flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
									printf(" flujo disponible en cuarta arista : %d \n " ,
									flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );
					//	}
		//	printf("asdasdvxcvxcv\n");

		}else{

			if ( arista_usada[ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] == 1 ) {

				if ( flujo_disponible_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] == 0){
					printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
					continue;
				}

				valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]];
				int temp = valores_minimos[fila];

				flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
				flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
				flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
				flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

				arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
				arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

				flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
				    flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
					flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
					flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
					flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
					flujos [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
					flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

				continue;
			}

			printf("\n");

			//2
			if ( arista_usada[ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] == 1 ) {

				if ( flujo_disponible_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] == 0){
					 printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
					 continue;
				}

				valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]];
				int temp = valores_minimos[fila];

				flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
				flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
				flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
				flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

				arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
				arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

				flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
					flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
					flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
					flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
					flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
					flujos [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
					flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

				continue;
			}

			printf("\n");

			// 3
			if ( arista_usada[ vertice[fila][ columna + 2 ]][ vertice[fila][ columna + 3 ]] == 1 ) {

				if ( flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] == 0){
					 printf("***no es posible recorrer este semicamino,el flujo ya esta saturado.fin de ejecucion \n ");
					 continue;
				}

				valores_minimos[fila] = flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]];
				int temp = valores_minimos[fila];

				flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = temp ;
				// flujo inverso ***
				flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna] ] = -temp ;
				flujo_total [vertice[fila][columna]][ vertice[fila][columna+1] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = temp ;
				flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += temp ;

				flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = temp ;
				flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += temp ;

				arista_usada[vertice[fila][ columna+1 ] ] [ vertice[fila][ columna + 2 ] ] = 1;
				arista_usada[vertice[fila][ columna+2 ] ] [ vertice[fila][ columna + 3 ] ] = 1;

				flujo_disponible_en_arista [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] =
					flujos [ vertice[fila][ columna ]][ vertice[fila][ columna + 1 ]] -
					flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] =
					flujos [ vertice[fila][ columna+1 ]][ vertice[fila][ columna + 2 ]] -
					flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ];
				flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] =
					flujo_disponible_en_arista [ vertice[fila][ columna+2 ]][ vertice[fila][ columna + 3 ]] -
					flujo_circulando_en_arista [vertice[fila][columna +2 ]][ vertice[fila][columna+3]];

				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+1 ],vertice[fila][columna+2]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2] ]);
				printf(" flujo circulando en arista (%d,%d) : %d  \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_circulando_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3] ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna ],vertice[fila][columna+1]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] );
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna +1 ],vertice[fila][columna+2]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]);
				printf( " flujo disponible en arista (%d,%d) : %d \n ",
					vertice[fila][ columna+2 ],vertice[fila][columna+3]  ,
					flujo_disponible_en_arista [ vertice[fila][ columna+2 ] ][ vertice[fila][columna+3]  ] );

				continue;
			}

			printf("\n");

			// si la arista no fue usada,usar el valor minimo de flujo del semicamino,
			//se busca el valor de flujo minimo en dos aristas adyacentes
			valores_minimos[fila] = min ( flujos [ vertice[fila][columna] ][vertice[fila][columna+1] ],
			flujos [ vertice[fila][columna+1] ][vertice[fila][columna+2] ]);

			// guardo la cantidad de flujo circulando en dos aristas,(valor de flujo minimo obtenido entre ellas dos)
			// y en ambas, las registro como usadas,por que ya contienen flujo circulando
			// y para controlar si la misma arista vuelve a ser usada por otro semicamino
			flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] =
				valores_minimos[fila] ;
			flujo_total	[ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] += valores_minimos[fila] ;
			arista_usada[ vertice[fila][ columna ] ][ vertice[fila][ columna + 1 ] ] = 1;
			//arista siguiente a la anterior
			flujo_circulando_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]  =
				valores_minimos[fila] ;
			flujo_total	[ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ] += valores_minimos[fila] ;
			arista_usada[ vertice[fila][ columna + 1 ] ][ vertice[fila][ columna + 2 ] ] = 1;

			printf ( "arista ya usada : (%d,%d ) \n ",vertice[fila][ columna ] , vertice[fila][ columna + 1 ]);
			printf ( "arista ya usada : (%d,%d ) \n ",vertice[fila][ columna+1 ],vertice[fila][columna+2]);

		    // actualizo el flujo disponible en dos aristas(capacidad),restandole el nuevo flujo que esta circulando
			flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ]  =
				flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] - valores_minimos[fila] ;

			flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] =
					flujos [ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] - valores_minimos[fila] ;

			//arista siguiente a la anterior
			flujo_disponible_en_arista [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ]  =
				flujos [ vertice[fila][ columna+1 ] ][ vertice[fila][columna+2]  ] - valores_minimos[fila] ;

			// se imprimen los flujos circulando en dos aristas,y el flujo disponible de cada una
			printf(" flujo circulando en arista (%d,%d) : %d  \n ",
				vertice[fila][ columna ],vertice[fila][columna+1]  ,
				flujo_circulando_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1] ]);
			printf(" flujo circulando en arista (%d,%d) : %d \n ",
				vertice[fila][ columna + 1 ],vertice[fila][ columna + 2 ]  ,
				flujo_circulando_en_arista [ vertice[fila][ columna + 1 ] ][ vertice[fila][ columna + 2 ] ]);
			printf( " flujo disponible en arista (%d,%d) : %d \n ",
				vertice[fila][ columna ],vertice[fila][columna+1]  ,
				flujo_disponible_en_arista [ vertice[fila][ columna ] ][ vertice[fila][columna+1]] );
			printf( " flujo disponible en arista (%d,%d) : %d \n ",
				vertice[fila][columna +1],vertice[fila][columna+2]  ,
				flujo_disponible_en_arista [vertice[fila][columna+1]][vertice[fila][columna+2]] );

			valor_anterior = valores_minimos[fila];
					// temp++;
			//	}

			// se guarda el valor de flujo de la tercer arista siguiente
			int temp2 = min ( flujos [ vertice[fila][columna+1] ][vertice[fila][columna+2] ],
				flujos [ vertice[fila][columna+2] ][vertice [fila][columna+3] ]) ;
			// se compara el valor minimo actual con el valor de flujo de la tercer arista

			if ( valor_anterior > temp2   )  {
				valores_minimos[fila] = temp2;

			//	arista_usada[ largo[control] ][i] = 1 ;
			//printf("valores minimos semicamino 1 %d : %d \n",control, valores_minimos[control]);
			flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] = valores_minimos[fila];
			flujo_total	[ vertice[fila][ columna ] ][ vertice[fila][columna+1]  ] += valores_minimos[fila] ;
			flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] = valores_minimos[fila];
			flujo_total [vertice[fila][columna+1]][ vertice[fila][columna+2] ] += valores_minimos[fila];
			flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
			flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] += valores_minimos[fila];

			flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] =
				flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ] -
				flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
			arista_usada[ vertice[fila][ columna + 2 ] ][ vertice[fila][ columna + 3 ] ] = 1;
			printf( " flujo circulando en primer arista : %d \n " ,
				flujo_circulando_en_arista [vertice[fila][columna]][ vertice[fila][columna+1] ] );
				//printf(" flujo disponible en tercer arista : %d \n " ,
				//flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

			printf( " flujo circulando en segunda arista : %d \n " ,
				flujo_circulando_en_arista [vertice[fila][columna+1]][ vertice[fila][columna+2] ] );
			//	printf(" flujo disponible en tercer arista : %d \n " ,
			//	flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

			printf( " flujo circulando en tercer arista : %d \n " ,
				flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
				printf(" flujo disponible en tercer arista : %d \n " ,
				flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

				}


			else{

					flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
					flujo_total [vertice[fila][columna+2]][ vertice[fila][columna+3] ] = valores_minimos[fila];
					flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] =
					flujos [ vertice[fila][columna+2] ][vertice[fila][columna+3] ] -
					flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] ;
					arista_usada[ vertice[fila][ columna + 2 ] ][ vertice[fila][ columna + 3 ] ] = 1;

					printf( " flujo circulando en tercer arista : %d \n " ,
					flujo_circulando_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3] ] );
					printf(" flujo disponible en tercer arista : %d \n " ,
					flujo_disponible_en_arista [vertice[fila][columna+2]][ vertice[fila][columna+3]] );

				}
		}
			printf( "\n" );
			}


	printf("flujos finales : \n");
	for (int var = 0 ; var < semicaminos_posibles ; var++ ) {
		printf("semicamino %d : ",var);
		for (int var2 = 0; var2 <  largo[var ]   ; ++var2 ) {
			printf( "  %d \t"  , vertice[var][var2] );
		}
		printf("flujo en semicamino %d : %d \n" ,var+1, valores_minimos[var]);


		//	int valores_de_flujos[ semicaminos_posibles+1 ];
	}

	//printf("largo en 3 : %d \n", largo[3] );

	fila = 0;
	columna = 0;

	printf( "flujo circulando en 0,1 : %d \n",flujo_total [ vertice [fila ][columna ] ][ vertice[fila][columna+1 ]] );
	printf( "flujo circulando en 0,2 : %d \n",flujo_total [ vertice [fila+2 ][columna ] ][ vertice[fila+2][columna+1 ] ] );
	printf( "flujo circulando en 3,5 : %d \n",flujo_total [ vertice [fila ][columna+2 ] ][ vertice[fila][columna+3 ]] );
	printf( "flujo circulando en 4,5 : %d \n",flujo_total [ vertice [fila+2 ][columna+2 ]  ][ vertice[fila+2][columna+3 ] ] );

	int flujo_fuente = flujo_total [ vertice [fila ][columna ]  ][ vertice[fila][columna+ 1] ] +
					   flujo_total [ vertice [fila+2 ][columna ]  ][ vertice[fila+2][columna+1 ] ]  ;

	int flujo_sumidero = flujo_total [ vertice [fila ][columna+2 ]  ][ vertice[fila][columna+3 ] ] +
						 flujo_total [ vertice [fila+2 ][columna+2 ]  ][ vertice[fila+2][columna+3 ] ]  ;

	printf("flujo de salida desde S : %d ", flujo_fuente   );
	printf("flujo de entrada a T : %d \n", flujo_sumidero    );

	//libero memoria
	for (int i = 0; i < semicaminos_posibles ; i++)
	{
	    int* currentIntPtr = ptr_semicamino[i];
	    free(currentIntPtr);
	}

	ptr_semicamino = NULL;
}
