/*
 * UVa 10130 - SuperSale
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1071
 *
 * He hecho este ejercicio puesto que es muy similar al 'problema de la mochila' del que hablamos.
 * En este caso, cada miembro del grupo que va a comprar representaría una mochila, y se nos pide la suma
 * del máximo que puede llevar cada miembro.
 * La dinámica está en optimizar valormax[i][j], que representa el valor máximo que se puede llevar teniendo
 * en cuenta los i primeros productos y con límite de peso j.
 * producto[i].first es el valor del producto i-ésimo, y producto[i].second su peso
 */

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<int,int> ParI;

int main() {
#ifndef ONLINE_JUDGE
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#endif
	int T, N, G, MW, i, calculado, suma;
	cin >> T;
	while( T-- ) {
		// Lectura de datos
		cin >> N;
		vector<ParI> producto(N);
		int valormax[N+1][31];
		for( i = 0; i < N; ++i ) {
			cin >> producto[i].first >> producto[i].second;
			valormax[i][0] = 0;
		}
		cin >> G;

		// Rellenar la tabla de valor máximo que se puede llevar
		calculado = 0;
		suma = 0;
		while( G-- ) {
			cin >> MW;
			while( MW > calculado ) {
				// Calcular valor máximo que se puede llevar con calculado+1 kilos
				valormax[0][calculado+1] = 0; // Llevando 0 productos, valor = 0
				for( i = 1; i < N+1; ++i ) {
					if( producto[i-1].second > calculado+1 ) // Si el producto es demasiado pesado, no lo podemos coger
						valormax[i][calculado+1] = valormax[i-1][calculado+1];
					else // Se decide cogerlo o no, dependiendo de lo que maximice el valor que podemos llevar
						valormax[i][calculado+1] = max( valormax[i-1][calculado+1], valormax[i-1][calculado+1-producto[i-1].second] + producto[i-1].first );
				}
				calculado++;
			}
			// Sumar el valor máximo que puede llevar cada miembro del grupo
			suma += valormax[N][MW];
		}

		cout << suma << endl;

	}

	return 0;
}
