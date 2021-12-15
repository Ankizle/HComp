#include <stdio.h>
#include "fetchexe.h"

int main()
{
    // TODO:
    //   get exe display and hoist it onto application window
    //   (maybe use zerovm?)

    // fetch exe from server
    // for now it's just a testing uri
    fetchEXE_SCP("usr@host:/file.bin");

    // use zerovm later for this step:
    system("file.bin");
}