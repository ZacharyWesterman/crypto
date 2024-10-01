from helper import *
from sys import argv

timer = Timer()

scoreDict = collateData(argv)

print(f"That took {timer.elapsed()}!\n\nDisplaying data... ", end='', flush=True)

plotData(scoreDict)

print("Exited.")
