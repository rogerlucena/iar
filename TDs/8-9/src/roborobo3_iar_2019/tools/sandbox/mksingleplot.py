#!/usr/bin/python

# 2017-1-29, nicolas
# trace (and save as PDF) a graph using CSV formatted data (single data points)

import os
import sys
import datetime
import time

from mylib import *

debug = True   # if True: shell command are not issued, but displayed.

if len(sys.argv) == 4 or len(sys.argv) == 5:
    filename = sys.argv[1]
    xIndex = int(sys.argv[2])
    yIndex = int(sys.argv[3])
    if len(sys.argv) == 5:
        prefix = sys.argv[4]
    else:
        prefix = ""
else:
    print "Clean file by filtering out all lines that do not begin with specified <prefix>"
    print "\tSyntax: ", sys.argv[0], " <file.ext> <x-axis index> <y-axis index> {<prefix>}"
    print "\tRemark: prefix may be omitted"
    print "\tRemark: axis indexes are considered after prefix removal"
    quit()

rawlines = getContentFromFile( filename )
rawlines = getLinesWithPrefix ( rawlines, prefix, True)

if debug == True:
    print rawlines

lines = parseLinesToArrayOfValues( rawlines )

if debug == True:
    print lines

xData = []
yData = []

for l in lines:
    xData.append( l[xIndex] )
    yData.append( l[yIndex] )
    print (str(l[xIndex])+","+str(l[yIndex]))

traceData( xData, yData, ylimMin=0, ylimMax=210, locLegend='lower right' )

