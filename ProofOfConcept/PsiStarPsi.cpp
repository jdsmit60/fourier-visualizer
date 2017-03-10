#include <fstream>
#include <iostream>
#include <iomanip>
#include <complex>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	// get or define all of the mathematical constants

	// get the coefficients from the file
	// the file should contain a space-separated or newline-separated list of 20 coefficients in the series

	if(argc != 2) {
		cout << "An input file is required. Exiting.\n";
	}

	ifstream inputFile;
	inputFile.open(argv[1]);

	if(!(inputFile.is_open())) {
		cout << "There was a problem opening the file. Exiting.\n";
	}

	double coefficient[20]; // assume that 20 coefficients will be used

	cout << "Coefficients:\n";

	for(int index = 0; index < 20; index++) {
		inputFile >> coefficient[index];
		cout << coefficient[index] << endl; // DEBUG
	}

	inputFile.close();

	// define other mathematical numbers of importance

	double hbar = 6.582e-16; // h bar (Planck's constant divided by 2*pi) in eV*seconds
	double mass = 5.11e25; // mass of particle in eV/c^2    5.11e25 is the mass of an electron
	double L = 1.0; // maximum position domain of Psi in Angstroms (assume the domain starts at 0)
	double domainStep = 0.01; // distance between points that will be calculated
	complex<double> i(0,1); // i = sqrt(-1)
	complex<double> Psi(0.0,0.0); // the intermediate result of the calculation
	double PsiSquared; // this will be the final result of the calculation

	// EVENTUALLY the coefficients will be normalized so that range is between 0 and sqrt(2),
	// but this does not appear to be the case right now so the range calculation remains.
	double minPsiSquared;
	double maxPsiSquared;

	double timeStep = 0.01*mass*L*L/(M_PI*hbar); // let the time step be the period of the most quickly oscillating term (term 20)
	double finalTime = 400.0*timeStep; // let the final time be the period of the least quickly oscillating term (term 1)
	int timeSteps = static_cast<int>(finalTime/timeStep);

	int digits = log10(timeSteps) + 1; // the number of digits to be used in the file name (small numbers are padded with leading zeros)

	// DEBUG

	cout << "\n\nOther Numbers:" << endl
	     << "hbar = " << hbar << endl
	     << "mass = " << mass << endl
	     << "L = " << L << endl
	     << "domainStep = " << domainStep << endl
	     << "timeStep = " << timeStep << endl
	     << "finalTime = " << finalTime << endl
	     << "timeSteps = " << timeSteps << endl
	     << "Psi = " << Psi << endl
	     << "i = " << i << endl;

	// get the output files ready

	ofstream dataFiles[timeSteps];
	stringstream filename; // using streams allows for the easy manipulation of the output file name

	for(int t = 0; t < timeSteps; t++) { // t is an index variable, not the actual variable t used in the equation

		// get the output file for this time step ready

		filename.str(string()); // reset the string in the filename stringstream to empty
		filename << "time" << setw(digits) << setfill('0') << t << ".dat";
		dataFiles[t].open(filename.str(), ios::out | ios::trunc);

			for(double x = 0.0; x <= L; x += domainStep) {

				for(int n = 1; n <= 20; n++) {
					Psi += coefficient[n-1]*sin(n*M_PI*x/L)*exp(i*(n*n*M_PI*M_PI*hbar/(2.0*mass*L*L))*(t*timeStep));
				}
				PsiSquared = norm(Psi);
				dataFiles[t] << x << " " << PsiSquared << endl;
			}

		dataFiles[t].close();

			if(t == 0) {
				minPsiSquared = maxPsiSquared = PsiSquared;
			}
			else {
				if(PsiSquared < minPsiSquared) {
					minPsiSquared = PsiSquared;
				}
				else if(PsiSquared > maxPsiSquared) {
					maxPsiSquared = PsiSquared;
				}
			}

	}
	ofstream range; // EVENTUALLY the coefficients will be normalized so that range is between 0 and sqrt(2),
	                // but this does not appear to be the case right now so the range calculation remains.
	range.open("range.dat", ios::out | ios::trunc);
	if(fabs(minPsiSquared - maxPsiSquared) < 0.001) {
		range << 0.75*minPsiSquared << ':' << 1.25*maxPsiSquared;
	}
	else {
		range << minPsiSquared << ':' << maxPsiSquared;
	}
	range.close();

}
