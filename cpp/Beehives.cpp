//============================================================================
// Name        : Beehives.cpp
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimo;
int recorridos[600];

void dfs(vector<vector<int> > listaAdyacencia, int padre, int previo, int actual, int pasos){

	if (pasos>minimo)					return;

	int size=listaAdyacencia[actual].size(),siguienteNodo;

	for (int i=0; i<size; i++){
		siguienteNodo=listaAdyacencia[actual][i];

		if (siguienteNodo==previo)		continue;

		if (recorridos[siguienteNodo]==-1){
			recorridos[siguienteNodo]=pasos;
			dfs(listaAdyacencia,padre,actual,siguienteNodo,pasos+1);
			recorridos[siguienteNodo]=-1;
		}
		else{
			minimo=min(minimo,pasos-recorridos[siguienteNodo]);
			return;
		}
	}


}


int main() {
	int T;
	cin >> T;
	for (int x=1;x<=T;x++){
		minimo=600;
		int n,m,u,v;
		cin >> n >> m;
		vector<vector<int> > listaAdyacencia(n);
		for (int i=0; i<600; i++)
			recorridos[i]=-1;

		while(m--){
			cin >> u >> v;
			listaAdyacencia[u].push_back(v);
			listaAdyacencia[v].push_back(u);
		}

		for (int i=0; i<n; i++)
			dfs(listaAdyacencia,0,0,0,0);

		cout << "Case " << x << ": ";
		if (minimo>550)	cout << "impossible" << endl;
		else			cout << minimo << endl;
	}
	return 0;
}
