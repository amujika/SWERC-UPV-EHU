/****************************************************************************
 *   Recorrido cíclico en un tablero de ajedrez dando saltos de caballo		*
 *   sin pasar dos veces por la misma casilla.								*
 *																			*
 *   Entrada: tres enteros -> N: tamaño del lado del tablero				*
 *   						  X: posición inicial (eje horizontal)			*
 *   						  Y: posición inicial (eje vertical)			*
 *																			*
 *   Salida: un cuadrado N*N numerado del 0 al (N*N)-1 donde el 0 es		*
 *   la casilla inicial y final y cada número indica el orden en el que		*
 *   se visitan las casillas.												*
 *   OJO: La solución sólo está asegurada para un N par >= 6				*
 *		 (teorema de Schwenk)												*
 *		 																	*
 *	 El algoritmo es un backtracking con heurística, pues un backtracking	*
 *	 que compruebe todos los casos es demasiado lento para un tablero 8x8.	*
 *	 La heurística implementada se llama "regla de Warnsdorff".				*
 *	 http://mirran.web.surftown.se/knight/eWarnsd.htm						*
 *																			*
 *	 Iván Matellanes - 27/10/2012											*
 *																			*
 ****************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

// Los 8 posibles movimientos
int MovX[] = { -1, -2, 1, 2, -1, -2, 1, 2 }, MovY[] = { -2, -1, -2, -1, 2, 1, 2, 1 };

// Muestra en pantalla la posible solución
void imprimir_solucion(const vector<vector<int> >& V, const int& N) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			cout << V[i][j] << "   ";
		cout << endl;
	}
	cout << endl;
}

// Backtracking: ocho posibles direcciones de avance
// T -> tablero con las casillas ya recorridas
// M -> movimientos posibles desde cada casilla
// Size -> tamaño del lado del tablero (n)
// X,Y -> casilla a la que va a avanzar el caballo
// Pasos -> pasos que se han dado hasta ahora
bool avanzar_casilla(vector<vector<int> > T, vector<vector<int> > M, const int Size, const int Y, const int X, const int Pasos) {
	// No se puede ir a una casilla fuera del tablero
	if (X < 0 || X >= Size || Y < 0 || Y >= Size)
		return false;

	// Última casilla tiene que ser la inicial
	if (Pasos == Size * Size) {
		if (T[Y][X] == 0) {
			imprimir_solucion(T, Size);
			return true;
		} else {
			return false;
		}
	}

	// Casilla ya recorrida: no vale
	if (T[Y][X] != -1)
		return false;

	// En caso contrario: avanzar una casilla más
	// Marcar la casilla actual como recorrida
	T[Y][X] = Pasos;
	// Reducir en uno el número de movimientos posibles desde las casillas adyacentes
	// y reordenar las direcciones según el número de movimientos posibles (Warnsdorff's rule)
	int i, k, MovOrdX[8], MovOrdY[8], movimientos = 0;
	for (k = 0; k < 8; ++k) {
		if (Y + MovY[k] >= 0 && Y + MovY[k] < Size && X + MovX[k] >= 0 && X + MovX[k] < Size) {
			M[Y + MovY[k]][X + MovX[k]]--;
			// Introduce el movimiento en el array de movimientos ordenados
			i = 0;
			while (i < movimientos && M[Y + MovOrdY[i]][X + MovOrdX[i]] <= M[Y + MovY[k]][X + MovX[k]])
				i++;
			for (int j = movimientos; j > i; --j) {
				MovOrdY[j] = MovOrdY[j - 1];
				MovOrdX[j] = MovOrdX[j - 1];
			}
			MovOrdY[i] = MovY[k];
			MovOrdX[i] = MovX[k];
			movimientos++;
		}
	}

	// Probar movimientos en todas las direcciones posibles
	k = 0;
	while (k < movimientos && !avanzar_casilla(T, M, Size, Y + MovOrdY[k], X + MovOrdX[k], Pasos + 1))
		k++;
	return (k != movimientos);
}

// Calcula el número de casillas accesibles desde cada posición del tablero
void calcular_movimientos_posibles(vector<vector<int> >& V, const int& N) {
	int cont;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cont = 0;
			for (int k = 0; k < 8; ++k)
				if (i + MovY[k] >= 0 && i + MovY[k] < N && j + MovX[k] >= 0 && j + MovX[k] < N)
					cont++;
			V[i][j] = cont;
		}
	}
}

int main() {
	int n, x, y;
	// Tamaño del tablero
	cin >> n;
	vector < vector<int> > Tablero(n, vector<int>(n, -1));
	vector < vector<int> > MovimientosPosibles(n, vector<int>(n));
	calcular_movimientos_posibles(MovimientosPosibles, n);
	// Casilla inicial
	cin >> x >> y;
	// Buscar soluciones
	if (!avanzar_casilla(Tablero, MovimientosPosibles, n, y, x, 0))
		cout << "No hay solución." << endl;
	return 0;
}
