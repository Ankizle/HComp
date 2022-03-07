import os

def getbenchmarks(end=".bin"):
    if not os.path.isdir("./build"): #check if the directory of the built files actually exists
        raise Exception("build directory not found")
    
    return filter(lambda x: x.endswith(end), os.listdir("./build"))