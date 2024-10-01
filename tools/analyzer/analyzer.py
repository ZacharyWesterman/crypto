from os import path, getcwd
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt

__location__ = path.realpath(
    path.join(getcwd(), path.dirname(__file__)))

program_path = __location__ + "/wikiAnalyzer"

p = Popen([program_path], stdout=PIPE)

scores: dict = {}

total = 0

while True:
  line = p.stdout.readline().strip().decode()

  if line == '':
    break

  numbers = [float(i) for i in line.split(',')]
  
  for n in numbers:
    total += 1
    n = int(n*10) / 10.0
    scores[n] = scores.get(n, 0) + 1

print(f"Displaying data ({total} values)... ", end='', flush=True)

plt.bar(list(scores.keys()), [i/total for i in list(scores.values())])
plt.title("Word Search Score Distribution")
plt.get_current_fig_manager().set_window_title("Analyzer")
plt.show()

print("Exited.")
