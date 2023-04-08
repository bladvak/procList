#ifndef PROCLIST_H
#define PROCLIST_H

#include <string.h>
#include <limits.h>
#include <stdio.h>

struct arguments{
    int basic; 
    char name[256];
    char pid[32];
};

const char* afterSubstr(const char* str, const char* sub);

void print_header(struct arguments* args);

int print_content(const char* dir_name, struct arguments* args);

void print_basic(FILE* fd);

#endif