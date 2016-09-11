#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include "counter.h"

// How long to go before we start rolling for a random stop, -1 is infinite
int minRandLen = -1;
// Chance of randomly stopping on once minRandLen reached, set between 0-100
int stopChance = 10;

// Runner variables
DIR *dir;
struct dirent *dp;
struct stat path;
char cwd[1024];
char fullpath[1024];

int p = 0; // Flag to print the path rather than to go there

int changer(char* path); // Function that changes path as provided by user
void runner(int len); // Function that runs through and acts on counter.c

int main(int argc, char* argv[]) {
    srand(time(NULL));
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
    runner(0);
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(1);
    } else {
        printf("%s%s\n", "The filepath is ", cwd);
    }
    return(0);
}

void runner(int len) {
    // Random stop chance process
    if (minRandLen != -1 && len >= minRandLen) {
        if ((rand() % 100) + 1 <= stopChance) {
            return;
        } 
    }
    // Find and change the directory as needed
    int chosendir = dirChoose();
    printf("%s%d\n", "Directory chosen: ", chosendir);
    if (chosendir == -1) {
        return;
    }
    int currentdir = 0;
    if ((dir = opendir(".")) == NULL) {
        perror("opendir");
        exit(1);
    }
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            memset(fullpath, '\0', sizeof(fullpath));
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("getcwd");
                exit(1);
            }
            // Set up full path
            strcpy(fullpath, cwd);
            strcat(fullpath, "/");
            strcat(fullpath, dp->d_name);
            // Stat it and check if it's a dir and executable
            if (stat(fullpath, &path) == -1) {
                perror("stat");
                exit(1);
            }
            if (S_ISDIR(path.st_mode) && S_IXUSR) {
                if (currentdir == chosendir) {
                    changer(fullpath);
                    break;
                }
                currentdir++;
            }
            memset(cwd, '\0', sizeof(cwd));
        }
    }
    runner(len + 1);
}

int changer(char* path) {
    if ((chdir(path))) {
        perror("chdir");
        return(1);
    }
    return(0);
}
