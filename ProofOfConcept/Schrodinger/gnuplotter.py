#!/bin/env python

import re
import os
import subprocess
import math

datFiles = []

for filename in os.listdir( "./datafiles" ):
	potentialMatch = re.match("time[0-9]*.dat",filename)
	if(potentialMatch):
		datFiles.append(potentialMatch.group())



datFiles.sort()

with open("./datafiles/range.dat","r") as rangefile:
	functionRange = rangefile.read()

digits = int(math.log10(len(datFiles)) + 1)

index = 0
for datFile in datFiles:
	command = "gnuplot -e \"set term pngcairo size 1280,960 truecolor enhanced; set output\'./imagefiles/gnuplot" + str(index).zfill(digits) + ".png\'; set style line 1 lt 1 lw 2 linecolor rgb \'#0099ff\'; set yrange [" + functionRange + "]; set xlabel \'Position x in meters\'; set ylabel \'Probability\'; plot \'./datafiles/" + datFile + "\' using 1:2 with lines smooth unique ls 1\""
	subprocess.Popen(command, shell=True, stdin=None, stdout=None, stderr=None)
	index += 1

# -pix_fmt yuv420p is essential here - otherwise videos will not play in browsers
# use os.system here so that ffmpeg exits properly - subprocess.Popen was causing issues
os.system("ffmpeg -i ./imagefiles/gnuplot%" + str(digits) + "d.png -vcodec h264 -r 25 -crf 18 -pix_fmt yuv420p -y graph.mp4 -nostdin")
