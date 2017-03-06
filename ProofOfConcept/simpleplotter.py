#!/bin/env python

import pylab
import numpy as np
import matplotlib.pyplot as plt
import re
import os

# this code used for experiments/understanding how these things work
#time0datx = np.loadtxt("time0.dat",usecols = 0)
#time0daty = np.loadtxt("time0.dat",usecols = 1)

#print(time0datx)
#print(time0daty)

#plt.plot(np.loadtxt("time0.dat",usecols = 0),np.loadtxt("time0.dat",usecols = 1))  # don't need to save columns to variables

#pylab.savefig('pyplot0.png')

# start actual program

datFiles = []

for filename in os.listdir( os.curdir ):
	potentialMatch = re.match('time[0-9]*.dat',filename)
	if(potentialMatch):
		datFiles.append((potentialMatch.group()))

datFiles.sort()

for datFile in datFiles:
	
