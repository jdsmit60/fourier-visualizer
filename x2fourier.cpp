// calculates Fourier series points for f(x) = x^2
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void) {
	double domainStart, domainEnd, domainStep; // graph domain variables, used for x
	long double latestY; // used for f(x)
	int L, upperLimit; // equation variables
	const double PI = 3.14159265358979323846264338;

	domainStart = -20;
	domainEnd = 20;
	domainStep = 0.01;
	L = 10;
	upperLimit = 500; // theoretically would be infinity for a perfect representation of the function

	for(double i=domainStart; i <= domainEnd; i+=domainStep) {
		
		latestY = 0;
		
		for(int n=1; n <= upperLimit; n++) {
			latestY += (/* start An */ (L*L*((2*PI*PI*n*n-1)*sin(2*PI*n)+2*PI*n*cos(2*PI*n)))/(2*pow(PI,3)*pow(n,3)) /* end An */)*cos(n*PI*i/L) + (/* start Bn */ (L*L*((1-2*PI*PI*n*n)*cos(2*PI*n)+2*PI*n*sin(2*PI*n)-1))/(3*pow(PI,3)*pow(n,3)) /* end Bn */)*sin(n*PI*i/L);
		}

		cout << setprecision(20) << i << " " << latestY << endl;

	}
	return 0;
}
