// compares the analytical value of the coefficients of a Fourier series
// to the numerically calculated value of the coefficient
// where the numerical method is Simpson's method with 100 subintervals


#include <complex>
#include <iostream>
#include <iomanip>

using namespace std;

double integratedFunc(double x1);
double AnIntegrand(double x1, int n, double L);
double BnIntegrand(double x1, int n, double L);
double simpsonsRuleAn(double left_endpoint, double right_endpoint, int n, double L);
double simpsonsRuleBn(double left_endpoint, double right_endpoint, int n, double L);

int main(void) {
	double L = 8;
	double k = 50.0;
	int upperLimit = 5;
	double analytical;
	double numerical;
	double error;

	cout << "An\n" << setprecision(10)
	     << "Analytical       Numerical       Error\n";

	for(int n=1; n <= upperLimit; n++) {
		analytical = (2*pow(L,3)*(M_PI*n*(M_PI*M_PI*n*n-6)*sin(M_PI*n)+3*(M_PI*M_PI*n*n-2)*cos(M_PI*n)+6))/(pow(M_PI,4)*pow(n,4));
		numerical = (2/L)*simpsonsRuleAn(0,L,n,L);
		error = fabs(analytical-numerical)/analytical*100;
		cout << analytical << "       " << numerical << "       " << error << "%\n";
	}

	cout << "\n\nBn\n"
	     << "Analytical       Numerical       Error\n";

	for(int n=1; n <= upperLimit; n++) {
		analytical = (-2*pow(L,3)*(M_PI*n*(n*n*M_PI*M_PI-6)*cos(M_PI*n)-3*(M_PI*M_PI*n*n-2)*sin(M_PI*n)))/(pow(M_PI,4)*pow(n,4));
		numerical = (2/L)*simpsonsRuleBn(0,L,n,L);
		error = fabs(analytical-numerical)/analytical*100;
		cout << analytical << "       " << numerical << "       " << error << "%\n";
	}

	return 0;
}

double simpsonsRuleAn(double left_endpoint, double right_endpoint, int n, double L) {

	double currentSum = 0;
	int intervals = 100;
	double deltax = (right_endpoint - left_endpoint)/intervals;

	for(int i=1; i <= intervals; i++) {
		currentSum += AnIntegrand(left_endpoint + (i-1)*deltax,n,L) + AnIntegrand(left_endpoint + (static_cast<double>(i) - 0.5)*deltax,n,L)
		              + AnIntegrand(left_endpoint + i*deltax,n,L);
	}
	
	return (deltax/3.0)*currentSum;
	
}

double AnIntegrand(double x1, int n, double L) {
	return integratedFunc(x1)*cos(n*M_PI*x1/L);
}

double integratedFunc(double x1) {
	return pow(x1,3);
}

double simpsonsRuleBn(double left_endpoint, double right_endpoint, int n, double L) {

	double currentSum = 0;
	int intervals = 100;
	double deltax = (right_endpoint - left_endpoint)/intervals;

	for(int i=1; i <= intervals; i++) {
		currentSum += BnIntegrand(left_endpoint + (i-1)*deltax,n,L) + BnIntegrand(left_endpoint + (static_cast<double>(i) - 0.5)*deltax,n,L)
		              + BnIntegrand(left_endpoint + i*deltax,n,L);
	}
	
	return (deltax/3.0)*currentSum;
	
}

double BnIntegrand(double x1, int n, double L) {
	return integratedFunc(x1)*sin(n*M_PI*x1/L);
}
