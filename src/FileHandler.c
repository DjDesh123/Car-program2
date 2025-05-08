#include "FileHandler.h"
#include <stdlib.h>

// to call the files to handle the file automation depending on the user's operating system
void fileRedirector(){
    //for windonws
    #ifdef _WIN32
        system("/include/setup/InventorySetUp.bat");
    //for linux/apple
    #else
        system("include/setup/InventorySetUp.sh");
    #endif // ends the ifdef}
}