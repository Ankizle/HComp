from build import *
from native import *
from hcomp import *
import matplotlib.pyplot as plt
import os
import numpy as np
import openpyxl as xl
import scipy.stats as sp

N_TRIALS = 30

def main():
    build()

    tot_native_data = []

    for i in range(0, N_TRIALS):
        print("NATIVE BENCHMARK #{}:".format(i + 1))
        tot_native_data.append(native_bench())
        print()
    print("------------------")
    print()

    tot_hcomp_data = []

    for i in range(0, N_TRIALS):
        print("HCOMP BENCHMARK #{}:".format(i + 1))
        tot_hcomp_data.append(hcomp_bench())
        print()
    print("------------------")
    print()

    #start plotting
    if not os.path.isdir("./dat"):
        os.mkdir("./dat/") #folder to store the dat

    benchnam = getbenchmarks()
    for b in benchnam:

        avg_native = 0
        avg_hcomp = 0
        vals_native = []
        vals_hcomp = []

        for m in tot_native_data:
            avg_native+=m[b]
            vals_native.append(m[b])
        for m in tot_hcomp_data:
            avg_hcomp+=m[b]
            vals_hcomp.append(m[b])

        outpath = "./dat/{}/".format(b)

        os.system("rm -rf {}".format(outpath))
        os.mkdir(outpath)

        #make excel project
        wb = xl.Workbook()
        ws = wb.active
        ws.title = b

        ws["A1"] = "Native"
        ws["C1"] = "HComp"

        for d in range(len(vals_native)):
            ws["A{}".format(d + 2)] = vals_native[d]

        for d in range(len(vals_hcomp)):
            ws["C{}".format(d + 2)] = vals_hcomp[d]

        ws["E1"] = "Averages:"
        ws["E2"] = "Native:"
        ws["F2"] = "=AVERAGE(A2:A{})".format(len(vals_native) + 1)
        ws["E3"] = "HComp:"
        ws["F3"] = "=AVERAGE(C2:B{})".format(len(vals_native) + 1)

        ws["H1"] = "Standard Deviations:"
        ws["H2"] = "Native:"
        ws["I2"] = "=STDEV(A2:A{})".format(len(vals_native) + 1)
        ws["H3"] = "HComp:"
        ws["I3"] = "=STDEV(C2:C{})".format(len(vals_native) + 1)

        dof = N_TRIALS - 1
        t_test = sp.ttest_ind(vals_native, vals_hcomp)
        pval = (1.0 - sp.t.cdf(abs(t_test.statistic), dof)) * 2.0
        ws["E5"] = "P-Value:"
        ws["F5"] = pval

        wb.save("{}dat.xlsx".format(outpath))

        avg_native/=len(tot_native_data)
        avg_hcomp/=len(tot_hcomp_data)

        native_stdev = np.std(np.array(vals_native))
        hcomp_stdev = np.std(np.array(vals_hcomp))

        plt.figure(0)

        plt.figure(0)
        plt.bar(range(0, 2), [avg_native, avg_hcomp], color=["blue", "orange"], yerr=[native_stdev, hcomp_stdev])
        
        plt.xticks(range(0, 2), ["Native", "HComp"])
        plt.ylabel("Execution speed in milliseconds")
        plt.title("Benchmarks")
        plt.savefig("{}graph.png".format(outpath))
        plt.close(0)


if __name__ == "__main__":
    main()