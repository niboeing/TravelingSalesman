import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as lines

print('Drawing last accepted path')

with open('cities.txt') as cityfile:
	tempcitylist = cityfile.read().splitlines()

citylist = list()

for el in tempcitylist:
	citylist.append(el.split(' '))
	
for i in range(len(citylist)):
	citylist[i][0] = int(citylist[i][0])
	citylist[i][1] = int(citylist[i][1])

with open('path.txt') as pathfile:
	pathlist = pathfile.read().splitlines()
pathlist = [int(i) for i in pathlist]
	
pointlist = list()
for i in range(len(citylist)):
	pointlist.append(citylist[pathlist[i]])
pointlist.append(citylist[pathlist[0]])


data = np.array(pointlist)
plt.axis('off')
plt.plot(data[:, 0], data[:, 1])
plt.show()
