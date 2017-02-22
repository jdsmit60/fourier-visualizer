# fourier-visualizer
A tool for visualization of Fourier series

I created this tool at first out of curiosity and out of frustration that the web app
Desmos was so slow for the kind of graphs I and my mentors were trying to generate.

Later the project became my official component of an honors project for my PHY 121
class in the Spring of 2017.

Each of the x[number]fourier.cpp files is C++ code that calculates all of the data
points for the Fourier series.

RunFourier.sh ties everything together by putting the output in the right place and 
passing that output into gnuplot to generate a graph.

RunFourier.sh also collects and displays some statistics about the calculation, such
as how long it took to run, the number of points generated, and the number of terms
used in each sum.
