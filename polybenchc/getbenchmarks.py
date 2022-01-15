import os

def getbenchmarks():
    if not os.path.isdir("./build"): #check if the directory of the built files actually exists
        raise Exception("build directory not found")
    
    return os.listdir("./build")