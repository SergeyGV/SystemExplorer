#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

int dirChoose() {
    DIR *dir;
    struct dirent *dp;
    struct stat path;
    char cwd[1024];
    char fullpath[1024];
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
            strcpy(fullpath, cwd);
            strcat(fullpath, "/");
            strcat(fullpath, dp->d_name);
            if (stat(fullpath, &path) == -1) {
                perror("stat");
                exit(1);
            }
            printf("%s\n", "FUCK FINALLY");
            memset(cwd, '\0', sizeof(cwd));
        }
    }
    return(0);
}
