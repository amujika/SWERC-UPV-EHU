#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Número de '1' que aparecen en el string S
int contar_unos(const string& s) {
	int res = 0;
	for (int i = 0; i < int(s.size()); ++i)
		if (s[i] == '1')
			res++;
	return res;
}

int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#endif
	int C, unos_S, unos_T, i;
	string S, T;
	cin >> C;
	for (int caso = 1; caso <= C; ++caso) {
		cin >> S >> T;
		unos_S = contar_unos(S);
		unos_T = contar_unos(T);
		if (unos_S > unos_T) {
			cout << "Case " << caso << ": -1" << endl;
		} else {
			int dif_unos = unos_T - unos_S, cambios = 0;
			// Quitar interrogantes
			for (i = 0; i < int(S.size()); ++i) {
				if (S[i] == '?') {
					if (dif_unos == 0) {
						S[i] = '0';
					} else {
						S[i] = T[i];
						if (T[i] == '1') dif_unos--;
					}
					cambios++;
				}
			}
			// Aqui S no tiene interrogantes
			// Si hay que meter más unos en S, cambiar 0 por 1 cuando interese
			for (i = 0; i < int(S.size()) && dif_unos > 0; ++i) {
				if (S[i] == '0' && T[i] == '1') {
					S[i] = '1';
					dif_unos--;
					cambios++;
				}
			}
			// Aqui S y T tienen mismo número de unos y de ceros
			// Buscar posiciones diferentes y swapear
			int difs = 0;
			for (i = 0; i < int(S.size()); ++i)
				if (S[i] != T[i])
					difs++;
			cambios += difs / 2;

			cout << "Case " << caso << ": " << cambios << endl;
		}
	}

	return 0;
}
