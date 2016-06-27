import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import math
import sys

with open(sys.argv[1], "r") as text_file:
	lines = np.array([int(x.strip('\n')) for x in text_file.read().split(',')])
	print "Average Edges needed for a cycle:",  np.mean(lines)
	print "Standard-deviation:", np.std(lines)
	plt.plot(lines, mlab.normpdf(lines, np.mean(lines), np.std(lines)))
	plt.show()
text_file.close()