#!/bin/bash

datfiles=(time*.dat)

#echo "${datfiles[@]}"

index=0

for file in "${datfiles[@]}"; do
printf "set term pngcairo size 640,480 truecolor enhanced; set output '%s'; set style line 1 lt 1 lw 3 linecolor rgb '#ff0000'; set yrange [%s]; plot '%s' using 1:2 with lines smooth unique ls 1\n" $(printf "plot%s.png" $index) $(cat range.dat) $(printf "time%s.dat" $index) | gnuplot
index=$(echo "$index + 1" | bc)
done
