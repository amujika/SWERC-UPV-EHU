#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Determina si el operador a tiene más preferencia que b
bool masPreferencia(const char& a, const char& b) {
	if( a == '(' ) return false;
	if( (a == '+' && b == '*') || (a == '-' && b == '*') ) return false;
	return true;
}

// Convierte la expresión infija s en postfija (notación polaca inversa)
string aPostfijo(const string& s) {
	string resultado;
	stack<char> pila;
	for( int i = 0; i < int(s.size()); ++i ) {
		if( s[i] == '(' ) {
			pila.push(s[i]);
		} else if( s[i] == '+' || s[i] == '-' || s[i] == '*' ) {
			while( !pila.empty() && masPreferencia(pila.top(),s[i]) ) {
				resultado += pila.top();
				pila.pop();
			}
			pila.push(s[i]);
		} else if( s[i] == ')' ) {
			while( !pila.empty() && pila.top() != '(' ) {
				resultado += pila.top();
				pila.pop();
			}
			if( !pila.empty() ) pila.pop(); // Sacar el abrir paréntesis
		} else { // Letra
			resultado += s[i];
		}
	}
	// Sacar lo que quede en la pila
	while( !pila.empty() ) {
		resultado += pila.top();
		pila.pop();
	}
	return resultado;
}

// Factorial desde 1 hasta 5 (pa' qué mas!)
int factorial( const int& i ) {
	switch(i) {
	case 1: return 1;
	case 2: return 2;
	case 3: return 6;
	case 4: return 24;
	case 5: return 120;
	}
	return 1;
}

// Evalua la expresión postfija e con los valores del vector v
int evaluar( const string& e, const vector<int>& v ) {
	stack<int> pila;
	int index = 0, op1, op2;
	for( int i = 0; i < int(e.size()); ++i ) {
		if( e[i] >= 'a' && e[i] <= 'z' ) {
			pila.push(v[index]);
			index++;
		} else {
			op2 = pila.top();
			pila.pop();
			op1 = pila.top();
			pila.pop();
			if( e[i] == '+' ) pila.push(op1+op2);
			else if( e[i] == '-' ) pila.push(op1-op2);
			else pila.push(op1*op2);
		}
	}
	return pila.top();
}

int main() {
#ifndef ONLINE_JUDGE
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#endif

	int n = -1, m = -1, i;
	string s;

	while( n != 0 || m != 0 ) {
		// Leer datos
		cin >> n;
		vector<int> valores(n);
		for( i = 0; i < n; ++i )
			cin >> valores[i];
		cin >> m;
		cin.ignore();

		if( n != 0 || m != 0 ) {
			// Parsear la expresión: notación postfija
			getline( cin, s );
			string expresion = aPostfijo(s);

			// Evaluar cada permutacion de las n! posibles hasta que se encuentre una buena o se prueben todas
			int posibilidades = factorial(n);
			bool coincidencia = false;
			i = 0;
			while( i < posibilidades && !coincidencia ) {
				if( evaluar(expresion,valores) == m )
					coincidencia = true;
				next_permutation( valores.begin(), valores.end() );
				i++;
			}

			// Dar resultado
			if( coincidencia )
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}

	return 0;
}
