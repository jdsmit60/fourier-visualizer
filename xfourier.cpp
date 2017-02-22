// calculates Fourier series points for f(x) = x
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
	L = 8;
	upperLimit = 100; // theoretically would be infinity for a perfect representation of the function

	for(double i=domainStart; i <= domainEnd; i+=domainStep) {
		
		latestY = 0;
		
		for(int n=1; n <= upperLimit; n++) {
			latestY += (/* start An */ (2*L*(PI*n*sin(PI*n)+cos(PI*n)-1))/(PI*PI*n*n) /* end An */)*cos(n*PI*i/L) + (/* start Bn */ (2*L*(sin(PI*n)-PI*n*cos(PI*n)))/(PI*PI*n*n) /* end Bn */)*sin(n*PI*i/L);
		}

		cout << setprecision(20) << i << " " << latestY << endl;

	}
	return 0;
}
