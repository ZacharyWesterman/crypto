from os import path, getcwd
from subprocess import Popen, PIPE
import numpy as np 
import matplotlib.pyplot as plt
from time import time
from itertools import combinations

__location__ = path.join(getcwd(), path.dirname(__file__))

analyzers = {"random": "red", "caesar": "blue", "wordSearch": "green", "spellCheck": "yellow"}

class Timer:
    def __init__(self): self.startTime = time()
    def elapsed(self): return self.formatTime(time() - self.startTime)
    # def formatTime(self, seconds): return f"{int(seconds) // (3600*24) % 24}d{int(seconds) // 3600 % 60}h{int(seconds) // 60 % 60}m{divmod(seconds, 60)[0] :.2f}s"
    def formatTime(self, seconds): return f"{seconds:.2f}s"

def getSubDicts(d): 
    return [dict(subset) for r in range(1, len(d)+1) for subset in combinations(d.items(), r)]

def parseOutput(program):
    p = Popen([path.join(__location__, "bin/", program)], stdout=PIPE)
    return [float(i) for line in p.stdout for i in line.decode().strip().split(',') if line]

def getData(args): 
    return {a: parseOutput(a + "Analyzer") for a in args.analyzers if a in analyzers}

def genStats(d):
    return "\n".join(f"{l}:\nMean: {np.mean(d_np):.2f}\nStddev: {np.std(d_np):.2f}\nMin: {np.min(d_np):.2f}\nMax: {np.max(d_np):.2f}\n" 
                     for l, d_np in ((l, np.array(d)) for l, d in d.items()))

def plotData(d, save):
    plt.clf()
    plt.title(" vs ".join(sorted(d.keys())) + " Score Distribution")
    plt.hist(d.values(), bins=50, label=d.keys(), color=[analyzers.get(k, 'gray') for k in d], histtype="stepfilled", edgecolor='black', alpha=0.5)
    plt.legend(loc='upper right')
    plt.gcf().text(0.85, 0.65, genStats(d), fontsize=10)
    plt.gcf().set_size_inches(21, 13)
    print("Rendering output... ", end='', flush=True)
    plt.savefig(f"{__location__}/output/{plt.gca().get_title()}.png", dpi=100) if save else plt.show()
    print("Done!")

def displayOutput(d, args): 
    print(genStats(d)) if args.text else plotData(d, args.save)

