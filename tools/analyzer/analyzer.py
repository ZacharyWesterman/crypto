from sys import argv
import time

from helper import *

startTime = time.time()

scoreDict = collateData(argv)

elapsedTime = formatTime(time.time() - startTime)

print(f"That took {elapsedTime}!\n\nDisplaying data... ", end='', flush=True)

plotData(scoreDict)

print("Exited.")
