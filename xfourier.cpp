// calculates Fourier series points for f(x) = x
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
	upperLimit = 100; // theoretically would be infinity for a perfect representation of the function

	for(double x=domainStart; x <= domainEnd; x+=domainStep) {
		
		latestY = 0;
		
		for(int n=1; n <= upperLimit; n++) {
			latestY += (/* start An */ (2*L*(M_PI*n*sin(M_PI*n)+cos(M_PI*n)-1))/(M_PI*M_PI*n*n) /* end An */)*cos(n*M_PI*x/L) + (/* start Bn */ (2*L*(sin(M_PI*n)-M_PI*n*cos(M_PI*n)))/(M_PI*M_PI*n*n) /* end Bn */)*sin(n*M_PI*x/L);
		}

		cout << setprecision(20) << x << " " << latestY << endl;

	}
	return 0;
}
