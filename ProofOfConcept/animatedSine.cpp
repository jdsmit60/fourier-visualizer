// generates many sets of points for a sine wave whose amplitude changes over time
// used for familiarization of passing data between C++ and matplotlib
// as well as creating animated plots

#include <complex>    // like cmath but handles complex numbers nicely
#include <fstream>
#include <string>
#include <sstream>    // stringstream

using namespace std;

int main(void) {
	int animationLength = 5; // seconds
	int frameRate = 24; // frames per second
	int timeSteps = animationLength*frameRate;
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
		filename << "time" << t << ".dat";
		datfiles[t].open(filename.str(), ios::out | ios::trunc);

		for(double x = domainStart; x <= domainEnd; x += domainStep) {
			latestY = (5.0 - static_cast<double>(t) / 24)*sin(x);
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
