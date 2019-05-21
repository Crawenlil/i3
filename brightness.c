#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define CIE_LEN 11


const char* mb = "/sys/class/backlight/intel_backlight/max_brightness";
const char* b = "/sys/class/backlight/intel_backlight/brightness";

int read_int(const char* path) {
    FILE* file = fopen(path, "r");
    int i = 0;
    fscanf(file, "%d", &i);    
    fclose(file);
    return i;
}

int write_int(const char* path, int i) {
    FILE* file = fopen(path, "w");
    if (file != NULL) {
        fprintf(file, "%d", i);    
        fclose(file);
        return 0;
    }
    return 1;
}

void cie1931(int n_values, int max_brightness, int * cie) {
    for(int i = 0; i < n_values; ++i){
        double l = i / (double) (n_values - 1);
        l *= 100;
        cie[i] =(int) round((l < 9 ? l/902.3 : pow((l+16) / 116.0, 3)) * max_brightness);
    }
}

int nearest_idx(const int brightness, int * cie, int cie_len) {
    int idx = 0;
    int diff = abs(brightness - cie[idx]); 
    while (idx+1 < cie_len && diff > abs(brightness - cie[idx+1])) {
        idx++;
        diff = abs(brightness - cie[idx]);
    }
    return idx;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Requires one argument!\n");
        return 1;
    }
    int direction = atoi(argv[1]);
    int brightness = read_int(b);
    int max_brightness = read_int(mb);
   
    int cie[CIE_LEN];
    cie1931(CIE_LEN, max_brightness, cie);

    int idx = nearest_idx(brightness, cie, CIE_LEN);
    idx = MIN(MAX(idx + direction, 0), CIE_LEN - 1);
    
    brightness = MIN(MAX(cie[idx], 0), max_brightness);

    return write_int(b, brightness);
}
