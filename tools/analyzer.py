import os
from subprocess import Popen, PIPE

__location__ = os.path.realpath(
    os.path.join(os.getcwd(), os.path.dirname(__file__)))

print(__location__)


program_path = __location__ + "/wordSearchEvaluator"

p = Popen([program_path], stdout=PIPE)

result = p.stdout.readline().strip()
