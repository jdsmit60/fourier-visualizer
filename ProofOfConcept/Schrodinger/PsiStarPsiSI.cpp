#include <fstream>
#include <iostream>
#include <iomanip>
#include <complex>
#include <iostream>

using namespace std;
const string outdir="./datafiles"; // use a separate directory for the data files to keep things clean

int main(int argc, char *argv[]) {
	// get or define all of the mathematical constants

	// get the coefficients from the file
	// the file should contain a space-separated or newline-separated list of the first 20 coefficients in the series

	if(argc != 2) {
		cout << "An input file is required. Exiting.\n";
		return 1;
	}

	ifstream inputFile;
	inputFile.open(argv[1]);

	if(!(inputFile.is_open())) {
		cout << "There was a problem opening the file. Exiting.\n";
		return 2;
	}

	double coefficient[20]; // assume that 20 coefficients will be used

	cout << "Coefficients:\n";

	for(int index = 0; index < 20; index++) {
		inputFile >> coefficient[index];
		cout << coefficient[index] << endl; // DEBUG
	}

	inputFile.close();

	// define other mathematical numbers of importance

	double hbar = 1.055e-34; // h bar (Planck's constant divided by 2*pi) in J*s
	double mass = 9.11e-31; // mass of particle in kg    9.11e-31 is the mass of an electron
	double L = 1.0e-10; // maximum position domain of Psi in meters (assume the domain starts at 0)
	double domainStep = L/100.0; // distance between points that will be calculated
	complex<double> i(0,1); // i = sqrt(-1)
	complex<double> Psi(0.0,0.0); // the intermediate result of the calculation
	double E_1 = (1.0/(2*mass))*pow(M_PI*hbar/L, 2); // ground-state energy
	double PsiSquared; // this will be the final result of the calculation

	// EVENTUALLY the coefficients will be normalized so that range is between 0 and sqrt(2),
	// but this does not appear to be the case right now so the range calculation remains.
	double maxPsiSquared = 0.0; // minPsiSquared is fixed at 0 so a variable is unneeded

	double timeStep = 3.3e-20; // let the time step be one tenth of the period of the most quickly oscillating term (term 20)
	double finalTime = 600.0*timeStep; // let the final time be the period of the least quickly oscillating term (term 1)
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

	for(int it = 0; it < timeSteps; it++) { // it is an index variable, not the actual variable t used in the equation

		double t = it*timeStep; // keep the equation clean by pre-computing the t that needs to be used in the equation

		// get the output file for this time step ready

		filename.str(string()); // reset the string in the filename stringstream to empty
		filename << outdir << "/time" << setw(digits) << setfill('0') << it << ".dat";
		dataFiles[it].open(filename.str(), ios::out | ios::trunc);

		if(!(dataFiles[it].is_open())) {
			cout << "Problem opening/creating data file. Exiting.\n";
			return 3;
		}

			for(double x = 0.0; x <= L; x += domainStep) {

				Psi = (0.0,0.0); // reset the value of Psi so that old values don't hang around

				for(int n = 1; n <= 20; n++) {
					Psi += coefficient[n-1]*sin(n*M_PI*x/L)*exp(i*(n*n*E_1/hbar)*t);
				}
				PsiSquared = norm(Psi);

				if(PsiSquared > maxPsiSquared) {
					maxPsiSquared = PsiSquared;
				}

				dataFiles[it] << x << " " << PsiSquared << endl;
			}

		dataFiles[it].close();

	}
	ofstream range; // EVENTUALLY the coefficients will be normalized so that range is between 0 and sqrt(2),
	                // but this does not appear to be the case right now so the range calculation remains.
	range.open(outdir + "/range.dat", ios::out | ios::trunc);

	if(!(range.is_open())) {
		cout << "Problem opening/creating range file. Exiting.\n";
		return 4;
	}

	if(fabs(maxPsiSquared) < domainStep) {
		range << "0:" << 1.25*maxPsiSquared;
	}
	else {
		range << "0:" << maxPsiSquared;
	}
	range.close();

}
