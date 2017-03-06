#include <fstream>
#include <complex>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

	// read in the values from the file

	if(argc != 2) {
		cout << "An input file is needed. Exiting.\n";
		return 1;
	}

	ifstream inputFile;
	inputFile.open(argv[1]);

	if(!inputFile.is_open()) {
		cout << "Could not open file. Exiting.\n";
		return 2;
	}

	double A, lambda, v;

	inputFile >> A >> lambda >> v;

	// DEBUG CODE

	cout << "A = " << A << endl << "lambda = " << lambda << endl << "v = " << v << endl;

	// start generating animation data

	int animationLength = 5; // seconds
	int framerate = 24; // frames per second
	int timeSteps = animationLength*framerate;
	ofstream datfiles[timeSteps];
	stringstream filename;

	double domainStart = -2*M_PI;
	double domainStep = 0.01;
	double domainEnd = 2*M_PI;
	double latestY;
	double minY;
	double maxY;

	for(int t = 0; t < timeSteps; t++) {
		filename.str(string()); // reset to blank name so that previous contents of the stream are erased
		filename << "time" << setw(log10(timeSteps) + 1) << setfill('0') << t << ".dat";
		datfiles[t].open(filename.str(), ios::out | ios::trunc);

		for(double x = domainStart; x <= domainEnd; x += domainStep) {
			latestY = A*sin((2*M_PI/lambda)*(x - v*(static_cast<double>(t)/framerate)));
			datfiles[t] << x << " " << latestY << endl;

			if(t == 0) {
				minY = maxY = latestY;
			}
			else {
				if(latestY < minY) {
					minY = latestY;
				}
				else if(latestY > maxY) {
					maxY = latestY;
				}
			}
		}
		datfiles[t].close();
	}
	ofstream range;
	range.open("range.dat", ios::out | ios::trunc);
	range << minY << ':' << maxY;
	range.close();
}
