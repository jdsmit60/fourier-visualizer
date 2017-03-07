#!/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import re
import os

datFiles = []

for filename in os.listdir( os.curdir ):
	potentialMatch = re.match("time[0-9]*.dat",filename)
	if(potentialMatch):
		datFiles.append(potentialMatch.group())



datFiles.sort()

with open("range.dat","r") as rangefile:
	functionRange = rangefile.read()

index = 0
for datFile in datFiles:
	command = "gnuplot -e \"set term pngcairo size 640,480 truecolor enhanced; set output\'gnuplot" + str(index) + ".png\'; set style line 1 lt 1 lw 3 linecolor rgb \'#ff0000\'; set yrange [" + functionRange + "]; plot \'" + datFile + "\' using 1:2 with lines smooth unique ls 1\""
	os.system(command)
	index += 1
