#include <iostream>
#include <cstdlib>

using namespace std;

int main() {

	int matriz[1000][1000];
	int n;
	cin >> n;

	while (n!=0){

		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++){
				cin >> matriz[i][j];
			}
		}

		int matriz2[1000][1000];

		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++){
				cin >> matriz2[i][j];
			}
		}

		int testigos[5][1000];
		for (int i=0; i<5; i++) {
			for (int j=0; j<1000; j++) {
				testigos[i][j]=rand();
			}
		}

		int testigos2[1000];

		bool iguales=true;
		for (int t=0; t<5 && iguales; t++) {

			for (int i=0; i<n; i++) {
				int v1 = 0;
				for (int k=0; k<n; k++) {
					v1 = v1 + matriz[i][k] * testigos[t][k];
				}
				testigos2[i] = v1;
			}

			for (int i=0; i<n && iguales; i++) {
					int v1 = 0;
					int v2 = 0;
					for (int k=0; k<n; k++) {
						v1= v1 + matriz[i][k] * testigos2[k];
						v2= v2 + matriz2[i][k] * testigos[t][k];
					}
					iguales = v1 == v2;
			}
		}

		if (iguales) {
			cout << "YES"<<endl;
		} else {
			cout << "NO"<<endl;
		}

		cin >> n;


	}

	return 0;
}
