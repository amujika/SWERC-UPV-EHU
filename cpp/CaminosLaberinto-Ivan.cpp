/**
 * Problema extraído de la web de la Olimpiada Informática
 * Enunciado: http://olimpiada-informatica.org/?cmd=downloadE&pbm=laberinth&ext=pdf
 *
 * Es un ejemplo sencillo de programación dinámica.
 * El número de caminos desde una determinada casilla (i,j) hasta la posición (0,0)
 * viene dado por Caminos[i][j]
 *
 * Iván Matellanes - 06/10/2011
 */

#include <iostream>
#include <vector>

#define MUCHO 1000000

using namespace std;
typedef unsigned long long ll;

int main()
{
    int Alto, Ancho;
    cin >> Alto >> Ancho;
    while( Alto != 0 && Ancho != 0 ) {
        vector< vector<char> > Laberinto( Alto, vector<char>(Ancho) );
        for( int i = 0; i < Alto; i++ )
            for( int j = 0; j < Ancho; j++ )
                cin >> Laberinto[i][j];

        vector< vector<ll> > Caminos( Alto, vector<ll>(Ancho) );
        // Establece los caminos en la primera fila y en la primera columna
        int Valor = 1;
        for( int i = 0; i < Alto; i++ ) {
            if( Laberinto[i][0] == 'X' ) Valor = 0;
            Caminos[i][0] = Valor;
        }
        Valor = 1;
        for( int j = 0; j < Ancho; j++ ) {
            if( Laberinto[0][j] == 'X' ) Valor = 0;
            Caminos[0][j] = Valor;
        }
        // Cuenta los caminos en todo el laberinto
        for( int i = 1; i < Alto; i++ ) {
            for( int j = 1; j < Ancho; j++ ) {
                if( Laberinto[i][j] == '.' ) Caminos[i][j] += Caminos[i-1][j] + Caminos[i][j-1];
                else Caminos[i][j] = 0;
            }
        }
        // Muestra el resultado
        if( Caminos[Alto-1][Ancho-1] >= MUCHO ) cout << "demasiados caminos" << endl;
        else cout << Caminos[Alto-1][Ancho-1] << endl;
        cin >> Alto >> Ancho;
    }

    return 0;
}
