#!/bin/bash

startTime=$(date +%s)
program=x3fourier
rm $program
g++ $program.cpp -o $program
./$program > points
echo 'set term pngcairo size 7680,4320 truecolor enhanced; set output "plot.png"; set style line 1 lt 1 lw 3 linecolor rgb "#ff0000"; plot "points"using 1:2 with lines smooth unique ls 1' | gnuplot
echo "Computed and rendered $(wc -l points) in $(echo "($(date +%s) - $startTime)" | bc) seconds using $(grep -P "^\tupperLimit" $program.cpp | awk ' {print $3} ' | sed 's/;//g') terms per sum"
