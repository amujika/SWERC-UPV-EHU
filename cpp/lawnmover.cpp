#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	double w;
	int nx,ny;
	bool b;
	cin >> nx >> ny >> w;
	while(nx!=0){	
	
		vector<double> x(nx);
		vector<double> y(ny);
	
		for (int i = 0; i<nx; i++)		cin >> x[i];
		for (int i = 0; i<ny; i++)		cin >> y[i];
	
		sort(x.begin(),x.end());
		sort(y.begin(),y.end());
	
		b=x[0]<=w/2 && y[0]<=w/2 && (75-x[nx-1])<=(w/2) && (100-y[ny-1])<=(w/2);
	
		for (int i = 1; i<nx && b; i++)		b=(x[i]-x[i-1])<=w;
		for (int i = 1; i<ny && b; i++)		b=(y[i]-y[i-1])<=w;
	
		if (b)	cout << "YES" << endl;
		else 	cout << "NO"  << endl;
		
		cin >> nx >> ny >> w;
	}
	return 0;
}
