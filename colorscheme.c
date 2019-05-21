#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_line(const char* path, const char* line){
    FILE* file = fopen(path, "w");
    if (file != NULL){
        fputs(line, file);
        fclose(file);
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]){
    char home[255];
    char path[255];
    char xrdb[255]; 
    strcpy(home, getenv("HOME"));
    strcpy(path, home);
    strcat(path, "/.colorscheme");
    strcpy(xrdb, "xrdb ");
    strcat(xrdb, home);
    strcat(xrdb, "/.Xresources");
    const char* light = "#define SOLARIZED_LIGHT 1";
    const char* dark  = "#define SOLARIZED_DARK 1";
    if (argc != 2){
        printf("Requires one argument!\n");
        return 1;
    }
    const char* line = argv[1];
    int exit_code = 0;
    if (strcmp(line, "solarized_dark") == 0){
        exit_code = write_line(path, dark); 
        system(xrdb);
    } else if (strcmp(line, "solarized_light") == 0){
        exit_code = write_line(path, light);
        system(xrdb); 
    } else {
        printf("Error, check .solarized file. It should contain SOLARIZED_DARK or SOLARIZED_LIGHT");
    }
    return exit_code;
}
