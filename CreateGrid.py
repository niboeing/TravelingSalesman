# Create a grid of cities

#set desired dimensions here
GridH = 10
GridW = 10

with open('cities.txt','w') as outfile:
	for i in range(GridH):
		for j in range(GridW):
			outfile.write(str(i)+' '+str(j)+'\n')
			
