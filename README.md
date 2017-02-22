# fourier-visualizer
A tool for visualization of Fourier series

## Project History
I created this tool at first out of curiosity and out of frustration that the web app
Desmos was so slow for the kind of graphs I and my mentors were trying to generate.

Later the project became my official component of an honors project for my PHY 121
class in the Spring of 2017.

## Basic Functionality
Each of the x[number]fourier.cpp files is C++ code that calculates all of the data
points for the Fourier series.

RunFourier.sh ties everything together by passing the output into gnuplot to generate a graph.

RunFourier.sh also collects and displays some statistics about the calculation, such
as how long it took to run, the number of points generated, and the number of terms
used in each sum.

## What's Next
1. Switch to [numerical approximation](https://en.wikipedia.org/wiki/Numerical_integration) of coefficients
  * I am currently leaning towards an [Adaptive Simpson's Method](https://en.wikipedia.org/wiki/Adaptive_Simpson's_method) algorithm
2. Use [GNU Getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html) to take command-line arguments for changeable variables instead of recompiling every time

## Eventual Goals
1. Animate the visualizations
2. Make the application portable
 * Switch from Bash to Python?
3. Improve performance by using multiple CPU threads
4. Create a GUI
