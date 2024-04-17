import matplotlib.pyplot as plt
import numpy as np
import math
import sys

fig, ax = plt.subplots()

with open("dist.txt", 'r') as file:
    dist = list(float(i) for i in file.readlines())

with open("dist.txt", 'r') as file:
    rep = list(float(i) for i in file.readlines())


index = []
for i in range(0, 769):
    index.append(i)

#ax.plot(index, dist)
#index, dist = np.histogram(x)
#plt.stairs(index, dist)
#plt.hist(dist, bins=20, alpha=1)
#plt.hist(index , bins=20, alpha=1)
#plt.hist(dist, color = 'blue', edgecolor = 'black', bins = int(180/5))
plt.bar(index, dist)
plt.title('Distribution', fontsize=20, fontname='Times New Roman')
plt.xlabel('index', color='black')
plt.ylabel('count',color='black')
plt.grid(True)
#plt.legend(['Mid Elem','Mid of 3', 'Random', 'Mid of 3 random'], loc=2)

print(math.sqrt(np.var(dist)))
#plt.show()
#plt.savefig('Graphics/hash.png')
plt.savefig(sys.argv[1])
