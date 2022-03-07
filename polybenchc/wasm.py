import os
import subprocess
from getbenchmarks import *

def wasm_bench():
    dat = {}

    for f in getbenchmarks():
        print("{} runtime: ".format(f), end="", flush=True)
        process = subprocess.Popen(["node", "./build/{}".format(f.split(".")[0] + ".js")], stdout=subprocess.PIPE)
        (out, e) = process.communicate()
        exit_code = process.wait()

        outstr = out.decode("utf-8")
        dat[f] = float(outstr) * 1000
        print(dat[f], end=" ms\n")

    return dat