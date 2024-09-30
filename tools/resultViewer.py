from sys import stdin
import matplotlib.pyplot as plt

scores: dict = {}

total = 0
for line in stdin:
  numbers = [float(i) for i in line.strip().split(',')]

  for n in numbers:
    total += 1
    n = int(n*10) / 10.0
    scores[n] = scores.get(n, 0) + 1

print("Displaying data... ", end='', flush=True)

plt.bar(list(scores.keys()), [i/total for i in list(scores.values())])
plt.title("Result Viewer")
plt.get_current_fig_manager().set_window_title("Word Search Score Distribution")
plt.show()

print("Exited.")
