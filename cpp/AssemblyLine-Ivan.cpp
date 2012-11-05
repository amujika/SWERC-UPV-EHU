/*
 * PROBLEMA H - SWERC 2010
 * "Assembly Line"
 *
 * En la web de UVa: 12276
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3428
 *
 * Iván Matellanes - 05/11/2012
 */

#include <fstream>
#include <iostream>

#define INF 2147483647

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#endif

	int num_simbolos, n = INF, i ,j, k, l, m;
	string s;
	while( cin >> num_simbolos && num_simbolos != 0 ) {
		// Salto de línea entre casos
		if( n != INF ) cout << endl;

		// Lectura de datos
		char simbolos[num_simbolos], resultado_conversion[num_simbolos][num_simbolos], guion;
		int tiempo_conversion[num_simbolos][num_simbolos];
		for( i = 0; i < num_simbolos; ++i )
			cin >> simbolos[i];
		for( i = 0; i < num_simbolos; ++i )
			for( j = 0; j < num_simbolos; ++j )
				cin >> tiempo_conversion[i][j] >> guion >> resultado_conversion[i][j];

		cin >> n;
		while( n-- ) {
			// Procesamiento de casos
			cin >> s;
			int len_total = s.length(), coste[len_total][len_total][num_simbolos];

			// Coste para subpalabras de longitud 1: desde i hasta i, 0 o infinito
			for( i = 0; i < len_total; ++i )
				for( j = 0; j < num_simbolos; ++j )
					if( s[i] == simbolos[j] )
						coste[i][i][j] = 0;
					else
						coste[i][i][j] = INF;


			// Coste para subpalabras de longitud 2 o más
			int longitud = 2, coste_minimo;
			while( longitud <= len_total ) {

				// Hallar coste de cada subpalabra de longitud 'longitud'
				// desde la posición 0 hasta (len_total - longitud), para todos los símbolos
				for( i = 0; i + longitud - 1 < len_total; ++i ) {

					// Subpalabra desde i a i+longitud-1
					// Su coste es: el menor de los costes entre las particiones en 2 de esa palabra que generen la letra que queremos
					for( j = 0; j < num_simbolos; ++j ) {
						coste_minimo = INF;

						// Probar las particiones solo cuando se puede generar el símbolo que buscamos (j)
						for( k = 0; k < num_simbolos; ++k )
							for( l = 0; l < num_simbolos; ++l )
								if( resultado_conversion[k][l] == simbolos[j] )
									for( m = i; m < i+longitud-1; ++m )
										if( coste[i][m][k] != INF && coste[m+1][i+longitud-1][l] != INF ) // Evitar conversión imposible
											coste_minimo = min( coste_minimo, coste[i][m][k] + coste[m+1][i+longitud-1][l] + tiempo_conversion[k][l] );

						coste[i][i+longitud-1][j] = coste_minimo;
					}

				}
				longitud++;
			}

			// Buscar el coste mínimo para convertir toda la palabra
			coste_minimo = INF;
			char resultado;
			for( i = 0; i < num_simbolos; ++i ) {
				if( coste[0][len_total-1][i] < coste_minimo ) {
					coste_minimo = coste[0][len_total-1][i];
					resultado = simbolos[i];
				}
			}

			cout << coste_minimo << "-" << resultado << endl;
		}
	}

	return 0;
}
