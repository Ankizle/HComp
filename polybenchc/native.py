import os
import subprocess
from getbenchmarks import *

def native_bench():
    dat = {}

    for f in getbenchmarks():
        print("{} runtime: ".format(f), end="", flush=True)
        process = subprocess.Popen(["./build/{}".format(f)], stdout=subprocess.PIPE)
        (out, e) = process.communicate()
        exit_code = process.wait()

        outstr = out.decode("utf-8")
        dat[f] = float(outstr)
        print(outstr, end="")

    return dat