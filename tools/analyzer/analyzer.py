from os import path, getcwd
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt
import numpy as np  # Import numpy for calculations
from sys import argv
import time

def formatTime(seconds):
    minutes, seconds = divmod(seconds, 60)
    hours, minutes = divmod(minutes, 60)
    days, hours = divmod(hours, 24)

    if days > 0:
        return f"{int(days)}d{int(hours)}h{int(minutes)}m{seconds:.2f}s"
    elif hours > 0:
        return f"{int(hours)}h{int(minutes)}m{seconds:.2f}s"
    elif minutes > 0:
        return f"{int(minutes)}m{seconds:.2f}s"
    else:
        return f"{seconds:.2f}s"

def analyzeOutput(program):
    __location__ = path.realpath(
        path.join(getcwd(), path.dirname(__file__)))

    program_path = __location__ + "/" + program

    p = Popen([program_path], stdout=PIPE)

    numbers = []

    while True:
        line = p.stdout.readline().strip().decode()

        if line == '':
            break

        numbers += [float(i) for i in line.split(',')]

    return numbers

def collateData(argv):
    scoreDict = {}

    if len(argv) == 1:
        scoreDict["wiki"] = analyzeOutput("wikiAnalyzer")
    else:
        for arg in argv[1:]:
            if arg == "caesar":
                scoreDict["caesar"] = analyzeOutput("caesarAnalyzer")
            elif arg == "wiki":
                scoreDict["wiki"] = analyzeOutput("wikiAnalyzer")

    return scoreDict  

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

startTime = time.time()

scoreDict = collateData(argv)
statTexts = genStats(scoreDict)

elapsedTime = formatTime(time.time() - startTime)

plt.title(" vs ".join(scoreDict.keys()) + " Score Distribution")
plt.hist(list(scoreDict.values()), bins=50, label=list(scoreDict.keys()), edgecolor='black')
plt.legend(loc='upper right')

# Improve how we're doing this
plt.gcf().text(0.85, 0.75, statTexts, fontsize=10, verticalalignment='center')

print(f"That took {elapsedTime}!\n\nDisplaying data... ", end='', flush=True)

plt.get_current_fig_manager().full_screen_toggle()
plt.show()

print("Exited.")
