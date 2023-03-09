# Import libraries
import matplotlib.pyplot as plt
import numpy as np

ress =  {'ABC': [34.54, 34.345, 34.761], 'DEF': [34.541, 34.748, 34.482]}
f = open("statistic.txt", "r")
info = "282,120,75,795,480,151,1449,1770,1726,2164,210,1235,1677,97,38,1476,664,1363,9368,81,566,3998,542,689,84,623,3184,7402,903,5445,10687,708,186,885,153,268,1182,1280,1122,3465,733,283,1295,447,492,78963,218,102,306,83"
infos = info.split(",")
infos = infos[0:-1]
# Creating dataset
res = [eval(i) for i in infos]


# Creating plot

plt.boxplot(res)

# show plot
plt.show()
