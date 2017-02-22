// calculates Fourier series points for f(x) = x^2
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void) {
	double domainStart, domainEnd, domainStep; // graph domain variables, used for x
	long double latestY; // used for f(x)
	int L, upperLimit; // equation variables

	domainStart = -20;
	domainEnd = 20;
	domainStep = 0.01;
	L = 10;
	upperLimit = 500; // theoretically would be infinity for a perfect representation of the function

	for(double i=domainStart; i <= domainEnd; i+=domainStep) {
		
		latestY = 0;
		
		for(int n=1; n <= upperLimit; n++) {
			latestY += (/* start An */ (L*L*((2*M_PI*M_PI*n*n-1)*sin(2*M_PI*n)+2*M_PI*n*cos(2*M_PI*n)))/(2*pow(M_PI,3)*pow(n,3)) /* end An */)*cos(n*M_PI*i/L) + (/* start Bn */ (L*L*((1-2*M_PI*M_PI*n*n)*cos(2*M_PI*n)+2*M_PI*n*sin(2*M_PI*n)-1))/(3*pow(M_PI,3)*pow(n,3)) /* end Bn */)*sin(n*M_PI*i/L);
		}

		cout << setprecision(20) << i << " " << latestY << endl;

	}
	return 0;
}
