from os import path, getcwd
from subprocess import Popen, PIPE
import numpy as np 
import matplotlib.pyplot as plt
from time import time
from itertools import combinations

__location__ = path.realpath(
    path.join(getcwd(), path.dirname(__file__)))

analyzers = {
    "random": "red",
    "caesar": "blue",
    "wiki": "green"
}

# Simple Timer
class Timer:
    def __init__(self):
        self.startTime = time()

    def formatTime(self, seconds):
        minutes, seconds = divmod(seconds, 60)
        hours, minutes = divmod(minutes, 60)
        days, hours = divmod(hours, 24)

        output = ""
        if days > 0:
            output += f"{int(days)}d"
        if hours > 0:
            output += f"{int(hours)}h"
        elif minutes > 0:
            output += f"{int(minutes)}m"
        output += f"{seconds:.2f}s"

        return output

    def elapsed(self):
        return self.formatTime(time() - self.startTime)

# Get an array of all subdictionaries from a dictionary
def getSubDicts(original_dict):
    result = []
    items = list(original_dict.items())
    
    for r in range(1, len(items) + 1):        # for all combo lengths...
        for subset in combinations(items, r): # for all combos...
            result.append(dict(subset))       # add them to results
    
    return result

# Actually listen to and return the output from a given script
def parseOutput(program):
    program_path = path.join(__location__, "bin/", program)
    p = Popen([program_path], stdout=PIPE)

    numbers = []
    while True:
        line = p.stdout.readline().strip().decode()
        if not line:
            break
        numbers += [float(i) for i in line.split(',')]

    return numbers

# Get all the data from all the outputs and group them together
def getData(args):
    scoreDict = {}

    for analyzer in args.analyzers:
        if analyzer not in analyzers:
            print(f"Invalid argument: {analyzer}")
            exit(1)
        scoreDict[analyzer] = parseOutput(analyzer + "Analyzer")

    return scoreDict

# Get summary statistics from the data set
def genStats(scoreDict):
    statTexts = []
    for label, data in scoreDict.items():
        data_np = np.array(data)
        mean = np.mean(data_np)
        stddev = np.std(data_np)
        min_val = np.min(data_np)
        max_val = np.max(data_np)

        statTexts.append(f"{label}:\nMean: {mean:.2f}\nStddev: {stddev:.2f}\nMin: {min_val:.2f}\nMax: {max_val:.2f}\n")
    
    return "\n".join(statTexts)

# Plot it all in matplotlib
def plotData(d, save):
    title = " vs ".join(sorted(d.keys())) 
    colors = [analyzers[key] if key in analyzers else 'gray' for key in d.keys()]
    values, labels = list(d.values()), list(d.keys())

    plt.title(title + " Score Distribution")
    plt.hist(values, bins=50, label=labels, color=colors, histtype="stepfilled", edgecolor='black', alpha=0.5)
    plt.legend(loc='upper right')

    plt.gcf().text(0.85, 0.65, genStats(d), fontsize=10, verticalalignment='center')
    plt.gcf().set_size_inches(21, 13)

    if save:
        print("Saving data... ", end='', flush=True)
        plt.savefig(__location__ + f"/output/{title}.png", dpi=100)
        print("Done!")
    else:
        print("Displaying data... ", end='', flush=True)
        plt.show()
        print("Closed!")

# display the output as requested by the user
def displayOutput(d, args):
    if args.text: 
        print(genStats(d))
    else:
      plotData(d, True if args.save else False)
        
