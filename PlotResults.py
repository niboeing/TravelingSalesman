import numpy as np
import matplotlib.pyplot as plt


print('Drawing plot of path lengths')

with open("log.txt") as infile:
	templist = infile.read().splitlines()

templist2 = list()
ListOfIt = list()
ListOfPath = list()
for el in templist:
	templist2 = el.split(' ')
	ListOfIt.append(templist2[0])
	ListOfPath.append(templist2[1])
	
plt.scatter(ListOfIt,ListOfPath)
plt.show()
