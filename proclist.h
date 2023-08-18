#ifndef PROCLIST_H
#define PROCLIST_H

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

struct arguments{
    bool basic;     // default pid, name, state
    bool vmemory; // -v
    bool group; // -g group
    bool ppid; //-p parent pid
    bool umask; // -u umask
    bool help; //-h 
};

char* afterSubstr( char* str, const char* sub);

void print_header(struct arguments* args);

int print_content(const char* dir_name, struct arguments* args);

void print_proc_info(FILE* fd, struct arguments* args);

void print_help();

#endif