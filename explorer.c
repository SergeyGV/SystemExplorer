#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// How long to go before we start rolling for a random stop, -1 is infinite
int minRandLen = -1;
// Chance of randomly stopping on once minRandLen reached, set between 0-100
int stopChance = 10;

int f; // Flag to indicate whether we include random stopping or not

int main(int argc, char* argv[]) {
    int f = 0;
    int c;
    while ((c = getopt(argc, argv, "f")) != -1) {
        switch (c) {
            case 'f':
                f = 1;
                break;
            default:
                printf("%s\n" , "usage: ./a.out [DIRPATH] [-f]");
                return(1);
        }
    }
    if (argc - optind > 1) {
        printf("%s\n" , "usage: ./a.out [DIRPATH] [-f]");
        return(1);
    }
    return(0);
}
