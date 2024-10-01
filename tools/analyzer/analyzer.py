from os import path, getcwd
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt
from sys import argv

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

scoreDict = {}

if len(argv) == 1:
  scoreDict["wiki"] = analyzeOutput("wikiAnalyzer")
else:
  for arg in argv[1:]:
    if arg == "caesar":
      scoreDict["caesar"] = analyzeOutput("caesarAnalyzer")
    elif arg == "wiki":
      scoreDict["wiki"] = analyzeOutput("wikiAnalyzer")

print(f"Displaying data... ", end='', flush=True)

plt.hist(list(scoreDict.values()), bins=50, label=list(scoreDict.keys()), edgecolor='black')
plt.title(" vs ".join(scoreDict.keys()) + " Score Distribution")
plt.get_current_fig_manager().set_window_title("Analyzer")
plt.legend(loc='upper right')

plt.show()

print("Exited.")
