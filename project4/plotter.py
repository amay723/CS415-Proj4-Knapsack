from matplotlib import use
use('Agg')
import matplotlib.pyplot as plt

from ast import literal_eval

def startPlot(LabelX, LabelY, Title):

    plt.title(Title)
    plt.xlabel(LabelX)
    plt.ylabel(LabelY)
    #plt.scatter(ListX, ListY)


def endPlot(save):
    #plt.ylim(bottom = 0, top = 2*ListY[0])
    #plt.xlim(left = 0, right = 2*max(ListX))
    plt.savefig(save)
    plt.clf()

def PlotPlot(filename):

    with open(filename, "r") as file:
        numitems = int( file.readline() )
        dtime = literal_eval( file.readline() )
        gtime = literal_eval( file.readline() )

    print("numitems =", numitems)
    print("dtime =", dtime, "; or %0.5f" % dtime)
    print("gtime =", gtime, "; or %0.5f" % gtime)


    plt.plot(numitems, dtime, 'bo')
    plt.plot(numitems, gtime, 'ro')


if __name__ == "__main__":
    LabelY = "Time (in ms)"
    LabelX = "Number of items -- Blue: Dynamic, Red: Greedy"
    Title = "Knapsack Dynamic approach vs Greedy Approach"
    startPlot(LabelX, LabelY,Title)
    for i in range(8):
        PlotPlot(f"plots{i}.txt")
    endPlot("OutputChart.png")
