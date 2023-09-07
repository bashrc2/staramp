#!/bin/bash
rm *.png
#./staramp --dog 8 --dogthresh 145 --dogamp 80 --miny 0 --maxy 2100 -f images/stars1.png
#./staramp --dog 12 --dogthresh 140 --dogamp 70 --miny 0 --maxy 0 --exclude "0,1590,1287,2013" -f images/stars2.png
./staramp --dog 12 --dogthresh 140 --dogamp 70 --miny 0 --maxy 0 --inside "(0,0),(3045,0),(3045,2019),(1278,2019),(936,1587),(0,1572)" -f images/stars2.png
