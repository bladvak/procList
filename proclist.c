#include "proclist.h"
#include <stdio.h>
#include <ctype.h>

//basic
#define PROC_NAME "Name:"
#define PID "Pid:"
#define STATUS "State:"
//optional
#define VMEM "VmSize:"
#define GROUP "Groups:"
#define PPID "PPid:"
#define UMASK "Umask:"


 char *afterSubstr( char *str, const char *sub)
{
     char* occurence;
    
    if( !(occurence = strstr(str, sub))) //instead use strtok and strcmp, beacuse this conditional result in true for PPid or TracerPid when testing for Pid
        return NULL;
    
    if(occurence > str)
        return NULL;

    return str + (occurence - str) + strlen(sub);
}

void print_header(struct arguments* args){
    if(args->basic)
        printf("%-32s", "Name");
    if(args->umask)
        printf("%-6s", "Umask");
    if(args->basic)
        printf("%-14s%-8s", "State","Pid");
    if(args->ppid)
        printf("%-8s", "PPid");
    if(args->group)
        printf("%-12s", "Groups");
    if(args->vmemory)
        printf("%-12s", "VirMemory");

    printf("\n");

    return;
}

char* onlyPrintable( char* str){
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
        print_proc_info(fd, args);

    return 1;
}

void print_proc_info(FILE *fd, struct arguments* args){
    char input[256];
     char name[128], pid[128], status[128];
     printf("%s","");
    while( fgets(input, 255, fd) ){
        char final[124];
        input[strcspn(input, "\n")] = 0;
         char* res;
        
        if( res = afterSubstr(input, PROC_NAME)){ //def
            strncpy(final, res, 36);
            printf("%-32.30s", onlyPrintable(final));
        }
        else if(args->umask && (res = afterSubstr(input, UMASK))){
            strncpy(final, res, 36);
            printf("%-6.5s", onlyPrintable(final));
        }
        else if( res = afterSubstr(input, STATUS)){ //def
            strncpy(final, res, 36);
            printf("%-14.12s", onlyPrintable(final));
        }
        else if( res = afterSubstr(input, PID)){ //def
            strncpy(final, res, 36);
            printf("%-8.7s", onlyPrintable(final));
        }
        else if(args->ppid && (res = afterSubstr(input, PPID))){
            strncpy(final, res, 36);
            printf("%-8.7s", onlyPrintable(final));
        }
        else if(args->group && (res = afterSubstr(input, GROUP))){
            strncpy(final, res, 36);
            printf("%-12.11s", onlyPrintable(final));
        }
        else if(args->vmemory && (res = afterSubstr(input, VMEM))){
            strncpy(final, res, 36);
            printf("%-12.11s", onlyPrintable(final));
        }
       
   }
  // printf("%-40s %-10s %-10s\n", onlyPrintable(name), onlyPrintable(pid), onlyPrintable(status));
   printf("\n");
   return;
}

void print_help(){
    printf("Usage: proclist [OPTIONS]\n-v      virtual memory\n"
    "-g     groups info\n-p     parent pid\n-u      umask\n"
    "-h      prints this information\n");
}