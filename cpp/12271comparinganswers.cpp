#include <iostream>
using namespace std;

int main() {

	int matriz[1000][1000];
	int n;
	cin >> n;

	while (n!=0){

		// La idea: se introducen los valores en una matriz de "conexiones" (la matrices que vimos con grafos el año pasado en M. Discreta) y se saca matriz^2. Eso tendrá todas las conexiones de longitud 2.
		
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++){
				cin >> matriz[i][j];
			}
		}

		int matriz2[1000][1000];

		// Orden n^3, el online judge no me lo admite porque tarda demasiado en ejecutarse (y no me extraña) ¿Alguna idea que sea más eficiente?
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				int v = 0;
				for (int k=0; k<n; k++) {
					v= v + matriz[i][k] * matriz[k][j];
					matriz2[i][j]=v;
				}
			}
		}

		int a;
		bool incorrect = false;
		for (int i=0; i<n; i++){
			for (int j=0; j<n; j++){
				cin >> a;
				if (!incorrect && a!=matriz2[i][j]){
					incorrect =true;
				}
			}
		}

		if (!incorrect) {
			cout << "YES"<<endl;
		} else {
			cout << "NO"<<endl;
		}

		cin >> n;


	}

	return 0;
}
