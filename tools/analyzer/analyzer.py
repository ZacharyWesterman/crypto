import argparse
from os import path, getcwd
from subprocess import Popen, PIPE
import numpy as np 
import matplotlib.pyplot as plt
from time import time

# TODO: Clean this up

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

# Get all the data from the cpp scripts we're running
def main():
    timer = Timer()

    parser = argparse.ArgumentParser(description="Plot score distributions from analyzers.")
    
    group = parser.add_mutually_exclusive_group()
    
    group.add_argument('--save', action='store_true', help="Save the plot as an image")
    group.add_argument('--show', action='store_true', help="Show the plot")
    group.add_argument('--stats', action='store_true', help="Show statistics in the terminal")
    
    parser.add_argument('analyzers', nargs='*', help="List of analyzers to use (default: 'wiki'). Use 'all' to include all analyzers.")
    
    args = parser.parse_args()

    if not (args.save or args.stats or args.show):
        args.show = True
    
    if not args.analyzers:
        args.analyzers = ['wiki']
    elif 'all' in args.analyzers:
        args.analyzers = list(analyzers.keys())
    
    scoreDict = {}
    for analyzer in args.analyzers:
        if analyzer not in analyzers:
            print(f"Invalid argument: {analyzer}")
            exit(1)
        scoreDict[analyzer] = parseOutput(analyzer + "Analyzer")


    print(f"\nThat took {timer.elapsed()}!\n")

    if not args.stats: 
        plotData(scoreDict)

    # Save or show the plot based on flags
    title = " vs ".join(scoreDict.keys())
    if args.save:
        print("Saving data... ", end='', flush=True)
        plt.savefig(__location__ + f"/output/{title}.png", dpi=100)
        print("Done!")
    elif args.show:
        print("Displaying data... ", end='', flush=True)
        plt.show()
        print("Closed!")
    elif args.stats:
        print(genStats(scoreDict))

    return scoreDict  

# Actually listen to and return the output from a given script
def parseOutput(program):
    program_path = path.join(__location__, program)
    p = Popen([program_path], stdout=PIPE)

    numbers = []
    while True:
        line = p.stdout.readline().strip().decode()
        if not line:
            break
        numbers += [float(i) for i in line.split(',')]

    return numbers

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
def plotData(scoreDict):
    title = " vs ".join(sorted(scoreDict.keys())) 
    colors = [analyzers[key] if key in analyzers else 'gray' for key in scoreDict.keys()]
    values, labels = list(scoreDict.values()), list(scoreDict.keys())

    plt.title(title + " Score Distribution")
    plt.hist(values, bins=50, label=labels, color=colors, histtype="stepfilled", edgecolor='black', alpha=0.5) # TODO: decide a histtype, try opacity
    plt.legend(loc='upper right')

    plt.gcf().text(0.85, 0.65, genStats(scoreDict), fontsize=10, verticalalignment='center')
    plt.gcf().set_size_inches(21, 13)

if __name__ == "__main__":
    main()
    