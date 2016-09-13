#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

int dirChoose() {
    // TODO: Error check Array Sizes
    DIR *dir;
    struct dirent *dp;
    struct stat path;
    char cwd[1024];
    char fullpath[1024];
    int dircounter = 0; // How many accessible directories there are
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
                //perror("stat");
                //exit(1);
            } else if (S_ISDIR(path.st_mode) && access(fullpath, X_OK) == 0) {
                dircounter++;
            }
            memset(cwd, '\0', sizeof(cwd));
        }
    }
	closedir(dir);
    // If above 1, return anywhere from 0 to dircount - 1
    // Else, return dircount - 1
    if (dircounter > 1) {
        return(rand() % dircounter);
    }
    return(dircounter - 1);
}
