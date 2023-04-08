#include "proclist.h"
#include <stdio.h>
#include <ctype.h>

#define PROC_NAME "Name:"
#define PID "NSpid:"
#define STATUS "State:"

const char *afterSubstr(const char *str, const char *sub)
{
    const char* occurence;
    if( !(occurence = strstr(str, sub)))
        return NULL;

    return str + (occurence - str) + strlen(sub);
}

void print_header(struct arguments* args){
    if(args->basic){
        printf("%-32s %-10s %-10s", "Name", "PID", "STATUS\n");
    }
}

char* onlyPrintable(const char* str){
    int i = 0;
    while(*(str+i) != '\0'){
        if( !isblank(*(str+i)))
        return str+i;
        i++;
    }
    return 0;
}

int print_content(const char* dir_name, struct arguments* args){
    FILE* fd; //at this point the dir name should be /proc/pid
    char path[255];
    strcpy(path, dir_name);
    strcat(path, "/status");

    if(!(fd = fopen(path, "r"))){
        printf("Cannot open %s", path);
        return 0;
    }

    if(args->basic)
        print_basic(fd);

    return 1;
}

void print_basic(FILE *fd){
    char input[256];
     char name[128], pid[128], status[128];
    while( fgets(input, 255, fd) ){
        input[strcspn(input, "\n")] = 0;
        char* res;
        if( res = afterSubstr(input, PROC_NAME))
            strcpy(name, res);
        else if ( res = afterSubstr(input, PID))
            strcpy(pid, res);
        else if( res = afterSubstr(input, STATUS))
            strcpy( status, res);  
   }
   printf("%-32s %-10s %-10s\n", onlyPrintable(name), onlyPrintable(pid), onlyPrintable(status));
   return;
}
