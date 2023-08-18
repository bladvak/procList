#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "proclist.h"

#define PROC_FOLDER "/proc/"



int main(int argc, char** argv){
struct arguments args;
args.basic = 1;

int opt;
while((opt = getopt(argc, argv, "vgpuh")) != -1){
    switch(opt) {
        case 'v': args.vmemory = true; break;
        case 'g': args.group = true; break;
        case 'p': args.ppid = true; break;
        case 'u': args.umask = true; break;
        case 'h': print_help(); exit(0);
        default: ;
    }
}


DIR* root_dir;

if( !(root_dir = opendir(PROC_FOLDER)) ){
    perror("Open /proc directory failed: ");
    return errno;
}

struct dirent* dir;
errno = 0;
print_header(&args);
while( (dir = readdir(root_dir)) && (!errno)){
    
    char pathname[1024]; //printf("\n--diagnostic pathname before strcpy: %s || d_name: %s\n", pathname, dir->d_name);
    strcpy(pathname, PROC_FOLDER); 
    strcat(pathname, dir->d_name); 
    
    if( !isdigit(dir->d_name[0]) /*&& !(S_ISDIR(st->st_mode))*/) //check if it's a pid dir(numbers only), commented: additionaly check if it's a dir
        continue;

   
    
    if(!print_content(pathname, &args)){
        perror("Error when processing... ");
        closedir(root_dir);
        exit(EXIT_FAILURE);  
    }   

}
if(errno){
    perror("When opening /proc subdirs: ");
    closedir(root_dir);
    exit(errno);
}
   
    
    closedir(root_dir); 
    
    return 0;
}