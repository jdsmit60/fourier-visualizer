#!/bin/env python

import pylab
import numpy as np
import matplotlib.pyplot as plt
import re
import os

datFiles = []

for filename in os.listdir( os.curdir ):
	potentialMatch = re.match('time[0-9]*.dat',filename)
	if(potentialMatch):
		datFiles.append(potentialMatch.group())

datFiles.sort()

index = 0
for datFile in datFiles:
	plt.figure()
	plt.plot(np.loadtxt(datFile,usecols = 0),np.loadtxt(datFile,usecols = 1))
	plotname = "pyplot" + str(index) + ".png"
	plt.savefig(plotname)
	plt.close()
	index += 1
