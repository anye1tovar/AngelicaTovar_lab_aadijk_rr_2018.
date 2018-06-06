#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
 
/* Definiendo la estructura etiqueta de nodo. Sus campos incluyen
 * el número de nodo, el coste total del nodo, y su precedente. */
struct label {
   int nro;	/* numero del nodo */
   int prev;	/* nodo precedente (-1 para el nodo inicial )*/
   int peso;	/* peso o coste total de la trayectoria que
				 * conduce al nodo, i.e., el coste total desde
				 * el nodo inicial hasta el actual. Un valor
				 * de -1 denota el infinito */
   int marca;	/* si el nodo ha sido marcado o no */
};
typedef struct label label_t;
 
using namespace std;

void dijkstra( int N, int **A, int a, int b ) {
 
   label_t *Labels;
   int i, i0, j, peso;
   int *ruta;		/* array de nodos de la ruta minima */
 
   /* Crea dinamicamente el arreglo de etiquetas de nodo */
   if ( ( Labels = new label_t[N] ) == NULL ) return;
 
   /* nodo inicial 'a' entre 0 y N - 1 */
   if ( a < 0 || a > N - 1 ) return;
   /* nodo final 'a' entre 0 y N - 1 */
   if ( b < 0 || b > N - 1 ) return;
 
   /* inicializar las etiquetas de nodo */
   for ( i = 0; i < N; i++ ) {
      Labels[i].nro = i;
      if ( i != a ) {
         Labels[i].prev = -1;	/* a'un no se ha definido predecesor */
         Labels[i].peso = -1;	/* infinito */
         Labels[i].marca = 0;
      }
      else {
         Labels[i].prev = -1;	/* a'un no se ha definido predecesor */
         Labels[i].peso = 0;		/* coste del nodo inicial a s'i mismo es cero */
         Labels[i].marca = 0;
      }
   }
 
   /* continuamos este ciclo mientras existan nodos no marcados */
   while ( 1 ) {
      /* busca entre todos los nodos no marcados el de menor peso, descartando los
       * de peso infinito (-1) */
      peso = -1;
      i0 = -1;
      for ( i = 0; i < N; i++ ) {
         if ( Labels[i].marca == 0 && Labels[i].peso >= 0 )
            if ( peso == -1 ) {
               peso = Labels[i].peso;
               i0 = i;
            }
            else if ( Labels[i].peso <= peso ) {
               peso = Labels[i].peso;
               i0 = i;
            }
      }
      if ( i0 == -1 ) {	/* termina si no encuentra */
         cout << "Ya no quedan nodos por analizar." << endl;
         break;
      }
 
      cout << "*** Analizando nodo " << i0 << " ***" << endl;
 
      /* actualiza el peso de todos los sucesores (si los hay) del nodo
       * encontrado y luego se~nala dicho nodo como marcado */
      for ( i = 0; i < N; i++ ) {
         if ( A[i0][i] > 0 ) {
            /* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
             * es menor al coste del nodo i (o si el coste del nodo i es infinito),
             * debemos actualizar */
            if ( Labels[i].peso == -1 || Labels[i0].peso + A[i0][i] < Labels[i].peso ) {
               if ( Labels[i0].peso + A[i0][i] < Labels[i].peso )
                  cout << "   [ mejorando coste de nodo " << i << " ]" << endl;
               Labels[i].peso = Labels[i0].peso + A[i0][i];
               Labels[i].prev = i0;
               cout << "   coste de nodo " << i << " desde nodo " << i0 << ": " << Labels[i].peso << endl;
            }
         }
      }
      Labels[i0].marca = 1;
      cout << "   [ nodo " << i0 << " marcado ]" << endl;
 
      /* para verificar, imprime los costes calculados hasta el momento */
      for ( i = 0; i < N; i++ ) {
         cout << i << ": [";
         if ( Labels[i].peso == -1 ) cout << "Inf";
         else cout << Labels[i].peso;
         cout << ", " << Labels[i].prev ;
         if ( Labels[i].marca == 1 ) cout <<  ", x]" << endl;
         else cout << "]" << endl;
      }
      cout << endl;
 
      /* pausa (opcional) */
      cout << "presione ENTER para continuar ...";
      cin.get();
   }
 
   /* Ruta desde el nodo 'a' hasta el nodo 'b' */
   int longitud = 2;
   i = b;
   while ( ( i = Labels[i].prev ) != a ) longitud++;	/* primero estimamos la longitud de la ruta */
   if ( ( ruta = new int[longitud] ) == NULL ) return;
 
   ruta[longitud - 1] = b;		/* luego rellenamos */
   i = b;
   j = 0;
   for ( j = 1; j < longitud; j++ ) {
      i = Labels[i].prev;
      ruta[longitud - j - 1] = i;
   }
 
   cout << "================================================================" << endl;
   cout << endl << "Ruta mas economica entre nodo " << a << " y nodo " << b << ":" << endl << endl;
   for ( i = 0; i < longitud; i++ ) {
      cout << ruta[i];
      if ( i < longitud - 1 ) cout << " - ";
   }
   cout << endl << endl << "Costo total: " << Labels[b].peso << endl << endl;
 
   delete ruta;
   delete [] Labels;
}

int main () {
	/* cantidad total de nodos */
   int numNodos;
	
	int v1, v2, c;
	ifstream fin;
	fin.open("erro.txt", ios::in);
	if(!fin.fail()){
		fin >> numNodos;
		
		/* Definiendo la matriz de adyacencia */
	   int i, j, **A;
	 
		if ( ( A = new int*[numNodos] ) == NULL ) return 1;
		for ( i = 0; i < numNodos; i++ )
			if ( ( A[i] = new int[numNodos] ) == NULL ) return 1;
	 
		for ( i = 0; i < numNodos; i++ )
	    	for ( j = 0; j < numNodos; j++ )
	        	A[i][j] = 0;
			
		while(fin >> v1 >> v2 >> c){
			A[v1][v2] = c;
		}
		fin.close();
		
		 
		/* Imprimir la matriz de adyacencia */
	   	cout << "Matriz de adyacencia:" << endl << endl;
	   	for ( i = 0; i < numNodos; i++ ) {
	    	for ( j = 0; j < numNodos; j++ )
	        	cout << setw(2) << A[i][j] << "  ";
	      	cout << endl;
	   	}
	   	cout << endl;
	 
	   	/* calcular dijkstra a partir del nodo 0, a partir del nofo 7 */
	   	dijkstra( numNodos, A, 0, 2);
	 
	   	/* liberar memoria */
	   	delete [] A;
	   	for ( i = 0; i < numNodos; i++ )
	      	delete A[i];
   	
	}
	else {
		cout << "Error ao abrir o arquivo" << endl;
		system("pause");
	}
   	return 0;
}
