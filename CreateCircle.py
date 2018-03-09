import sys
import math
import numpy as np

if not len(sys.argv)==3:
	print('Usage: python3 CreateCircle.py <radius> <no of points>')
	sys.exit()
	
try:
	radius = float(sys.argv[1])
	anglestep = 360/float(sys.argv[2])
except:
	print('[ERROR] Couldn\'t convert values, use floats only')
	sys.exit()

angles = np.arange(0.0,360.0,anglestep)
print(angles)
with open('cities.txt','w') as outfile:
	for angle in angles:
		x = math.cos(angle*math.pi/180)*radius
		y = math.sin(angle*math.pi/180)*radius
		outfile.write(str(x)+' '+str(y)+'\n')
