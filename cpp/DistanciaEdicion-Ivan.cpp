/**
 * Problema extraído de la web de la Olimpiada Informática
 * Enunciado: http://olimpiada-informatica.org/?cmd=downloadE&pbm=distancia1&ext=pdf
 *
 * Otro ejemplo de programación dinámica.
 * La pista del enunciado creo que lo deja bastante claro.
 *
 * Iván Matellanes - 06/10/2011
 */

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int Letras;
    while( cin >> Letras ) {
        vector<int> C(Letras);
        for( int i = 0; i < Letras; ++i ) cin >> C[i];
        string a, b;
        cin >> a >> b;

        int SA = a.size(), SB = b.size();
        vector< vector<int> > T( SA+1, vector<int>(SB+1) );
        for( int i = 1; i <= SA; ++i ) T[i][0] = T[i-1][0] + C[a[i-1]-'a'];
        for( int i = 1; i <= SB; ++i ) T[0][i] = T[0][i-1] + C[b[i-1]-'a'];
        for( int i = 1; i <= SA; ++i )
            for( int j = 1; j <= SB; ++j ) {
                if( a[i-1] == b[j-1] ) {
                    T[i][j] = T[i-1][j-1];
                } else {
                    T[i][j] = min( T[i][j-1] + C[b[j-1]-'a'], T[i-1][j] + C[a[i-1]-'a'] );
                }
            }
        cout << T[SA][SB] << endl;
    }

    return 0;
}
