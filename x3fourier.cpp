// calculates Fourier series points for f(x) = x^3
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
	L = 8;
	upperLimit = 500; // theoretically would be infinity for a perfect representation of the function

	for(double i=domainStart; i <= domainEnd; i+=domainStep) {
		
		latestY = 0;
		
		for(int n=1; n <= upperLimit; n++) {
			latestY += (/* start An */ (2*pow(L,3)*(M_PI*n*(M_PI*M_PI*n*n-6)*sin(M_PI*n)+3*(M_PI*M_PI*n*n-2)*cos(M_PI*n)+6))/(pow(M_PI,4)*pow(n,4)) /* end An */)*cos(n*M_PI*i/L) + (/* start Bn */ (-2*pow(L,3)*(M_PI*n*(n*n*M_PI*M_PI-6)*cos(M_PI*n)-3*(M_PI*M_PI*n*n-2)*sin(M_PI*n)))/(pow(M_PI,4)*pow(n,4)) /* end Bn */)*sin(n*M_PI*i/L);
		}

		cout << setprecision(20) << i << " " << latestY << endl;

	}
	return 0;
}
