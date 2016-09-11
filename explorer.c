#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "counter.h"

// How long to go before we start rolling for a random stop, -1 is infinite
int minRandLen = -1;
// Chance of randomly stopping on once minRandLen reached, set between 0-100
int stopChance = 10;

int p = 0; // Flag to print the path rather than to go there

int changer(char* path); // Function that changes path as provided by user

int main(int argc, char* argv[]) {
    int c;
    while ((c = getopt(argc, argv, "fp")) != -1) {
        switch (c) {
            case 'f': // Flag if we should randomly stop or not
                stopChance = 0;
                break;
            case 'p':
                p = 1;
                break;
            default:
                printf("%s\n" , "usage: ./a.out [DIRPATH] [-f] [-p]");
                return(1);
        }
    }
    if (argc - optind > 1) {
        printf("%s\n" , "usage: ./a.out [DIRPATH] [-f] [-p]");
        return(1);
    } else if (argc - optind == 1) {
        if ((changer(argv[argc - 1]))) {
            return(1);
        }
    }
    return(0);
}

int changer(char* path) {
    if ((chdir(path))) {
        perror("chdir");
        return(1);
    }
    return(0);
}
