from os import path, getcwd
from subprocess import Popen, PIPE
import numpy as np 
import matplotlib.pyplot as plt
from time import time

__location__ = path.realpath(
    path.join(getcwd(), path.dirname(__file__)))

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
            output += f"{int(minutes)}"

        output += f"{seconds:.2f}s"

        return output

    def elapsed(self):
        return self.formatTime(time() - self.startTime)

# Get all the data from the cpp scripts we're running
def collateData(argv):
    scoreDict = {}
    analyzers = ["random", "caesar", "wiki"]

    if len(argv) == 1:
        argv = ["", "wiki"]
    elif argv[1] == "all":
        argv = ["", *analyzers]

    for arg in argv[1:]:
        if arg not in analyzers:
            print ("Invalid argument")
            exit()

        scoreDict[arg] = parseOutput(arg + "Analyzer")

    return scoreDict  

# Actually listen to and return the output from a given script
def parseOutput(program):

    program_path = __location__ + "/" + program

    p = Popen([program_path], stdout=PIPE)

    numbers = []

    while True:
        line = p.stdout.readline().strip().decode()

        if line == '':
            break

        numbers += [float(i) for i in line.split(',')]

    return numbers

# Get sume of the statistical values from the data set
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
    title = " vs ".join(scoreDict.keys()) 
    plt.title(title+ " Score Distribution")
    plt.hist(list(scoreDict.values()), bins=50, label=list(scoreDict.keys()), edgecolor='black')
    plt.legend(loc='upper right')

    # Improve how we're doing this
    plt.gcf().text(0.85, 0.65, genStats(scoreDict), fontsize=10, verticalalignment='center')
    plt.gcf().set_size_inches(21, 13)

    plt.get_current_fig_manager().full_screen_toggle()
    plt.savefig(__location__ + f"/output/{title}.png", dpi=100)
    plt.show()
