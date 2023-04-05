#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "proclist.h"

#define PROC_FOLDER "/proc/"

int main(int argc, char** argv){

DIR* root_dir;

if( !(root_dir = opendir(PROC_FOLDER)) ){
    perror("Open /proc directory failed: ");
    return errno;
}

struct dirent* dir;
errno = 0;
while( (dir = readdir(root_dir)) || (!errno)){
    //struct stat* st; char pathname[30];
   // strcpy(pathname, PROC_FOLDER); strcat(pathname,dir->d_name);
    //stat(pathname, st);
    if( !isdigit(dir->d_name[0]) /*&& !(S_ISDIR(st->st_mode))*/) //check if it's a pid dir(numbers only), commented: additionaly check if it's a dir
        continue;

    printf("%s\n", dir->d_name); //from here start processing status files in dir
}
if(!errno){
    perror("When opening /proc subdirs: ");
    exit(errno);
}
    
    
    closedir(root_dir); 
    return 0;
}