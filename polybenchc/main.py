from build import *
from native import *
from hcomp import *
import matplotlib.pyplot as plt
import os
import numpy as np

def main():
    build()
    print("NATIVE BENCHMARK:")
    native_data = native_bench()
    print()

    print("HCOMP BENCHMARK")
    hcomp_data = hcomp_bench()
    print()

    #start plotting
    if not os.path.isdir("./plots"):
        os.mkdir("./plots/") #folder to store the plots

    benchnam = getbenchmarks()
    for b in benchnam:
        plt.figure(0)
        plt.bar(range(0, 2), [native_data[b], hcomp_data[b]], color=["blue", "orange"])
        
        plt.xticks(range(0, 2), ["Native", "HComp"])
        plt.ylabel("Execution speed in seconds")
        plt.title("Benchmarks")
        plt.legend()
        plt.savefig("./plots/{}.png".format(b))
        plt.close(0)

if __name__ == "__main__":
    main()