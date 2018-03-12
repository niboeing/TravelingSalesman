import sys
import math
import numpy as np

def PrintUsageInfo():
	print('Usage: python3 CreateCities.py <shape> <parameter 1> <parameter 2> ...')
	print('Options:')
	print('circle <radius> <no of points>')
	print('grid <width> <height>')
	print('islands <width> <height> <distance>')
	
if not len(sys.argv)>=4:
	PrintUsageInfo()
	sys.exit()

#OPTION CIRCLE
if str(sys.argv[1]).lower() == 'circle':	
	try:
		radius = float(sys.argv[2])
		anglestep = 360/float(sys.argv[3])
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
	sys.exit()

#OPTION GRID			
if str(sys.argv[1]).lower() == 'grid':
	try:
		GridH = int(sys.argv[2])
		GridW = int(sys.argv[3])
	except:
		print('[ERROR] Couldn\'t convert values, use integers only')
		sys.exit()
	
	with open('cities.txt','w') as outfile:
		for i in range(GridH):
			for j in range(GridW):
				outfile.write(str(i)+' '+str(j)+'\n')
	sys.exit()
	
#OPTION ISLANDS
if str(sys.argv[1]).lower() == 'islands':
	try:
		GridH = int(sys.argv[2])
		GridW = int(sys.argv[3])
		Distance = int(sys.argv[4])
	except:
		print('[ERROR] Couldn\'t convert values, use integers only')
		sys.exit()
		
	with open('cities.txt','w') as outfile:
		for i in range(GridH):
			for j in range(GridW):
				outfile.write(str(i)+' '+str(j)+'\n')
		for i in range(GridH):
			for j in range(GridW+Distance,2*GridW+Distance):
					outfile.write(str(i)+' '+str(j)+'\n')
	sys.exit()

print('[ERROR] Couldn\'t find this option')
PrintUsageInfo()
