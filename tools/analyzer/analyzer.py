from helper import *
import argparse

def reprocessArgs(args):
    if not (args.save or args.text or args.view):
        args.view = True

    if not args.analyzers:
        args.analyzers = ['wordSearch']
    elif 'all' in args.analyzers:
        args.analyzers = list(analyzers.keys())

    return args


def main():
    timer = Timer()

    parser = argparse.ArgumentParser(description="Plot score distributions from analyzers.")

    group = parser.add_mutually_exclusive_group()
    
    group.add_argument('-s', '--save', action='store_true', help="Save the plot as an image")
    group.add_argument('-v', '--view', action='store_true', help="View the plot")
    group.add_argument('-t', '--text', action='store_true', help="Show statistics in the terminal")
    
    parser.add_argument('-r', '--recursive', action='store_true', help="Display all subsets of the input as well")

    parser.add_argument('analyzers', nargs='*', help="List of analyzers to use (default: 'wordSearch'). Use 'all' to include all analyzers.")
    
    args = reprocessArgs(parser.parse_args())
    
    scoreDict = getData(args)

    print(f"\nThat took {timer.elapsed()}!\n")

    results = getSubDicts(scoreDict) if args.recursive else [scoreDict]

    for d in results:
        displayOutput(d, args)

if __name__ == "__main__":
    main()
    