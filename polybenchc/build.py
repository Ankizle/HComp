import os

parents = [
    "datamining",
    "linear-algebra",
    "medley",
    "stencils",
]

def build():

    #make a build directory to output the binaries to
    clean()
    os.system("mkdir ./build")

    for p in parents:
        for path, directories, files in os.walk("./{}".format(p)):
            '''
            Command to compile a benchmark with time measurement
            gcc -O3 -I utilities -I <path-to-directory> utilities/polybench.c <path-to-start> -DPOLYBENCH_TIME -o <output> -lm
            '''

            for f in files:  
                if f[-1] == "c":
                    #it's the main c file
                    os.system(
                        "gcc -O3 -I utilities -I {} utilities/polybench.c {} -DPOLYBENCH_TIME -o {} -lm"
                        .format(
                            path, #path to directory of benchmark
                            path + "/" + f, #path to main file of benchmark
                            "./build/{}.bin".format(f), #path to output build to
                        )
                    )

def clean():
    os.system("rm -r ./build")