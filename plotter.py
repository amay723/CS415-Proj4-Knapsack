from matplotlib import use
use('Agg')
import matplotlib.pyplot as plt

from ast import literal_eval

def Scattering(ListX, ListY, save, LabelX, LabelY, Title, bound):
    if (bound == True):
        plt.ylim(bottom = 0, top = 2*ListY[0])
        plt.xlim(left = 0, right = 2*max(ListX))
    plt.title(Title)
    plt.xlabel(LabelX)
    plt.ylabel(LabelY)
    #plt.scatter(ListX, ListY)
    plt.plot(ListX[0], ListY[0], 'bo')
    plt.plot(ListX[1], ListY[1], 'ro')
    plt.savefig(save)
    plt.clf()


file = open("plots.txt", "r")

numitems = int( file.readline() )
dtime = literal_eval( file.readline() )
gtime = literal_eval( file.readline() )

file.close()

print("numitems =", numitems)
print("dtime =", dtime, "; or %0.5f" % dtime)
print("gtime =", gtime, "; or %0.5f" % gtime)

y = [dtime, gtime]
x = [numitems, numitems]

LabelY = "Time (in ms)"
LabelX = "Number of items -- Blue: Dynamic, Red: Greedy"
Title = "Knapsack Dynamic approach vs Greedy Approach"

Scattering(x, y, "KnapsackTimePlots.png", LabelX, LabelY, Title, True)
