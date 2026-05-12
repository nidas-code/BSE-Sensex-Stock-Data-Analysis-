#include <cstdio>
#include "data_reader.h"

void loadData(SensexEntry data[], int &size) {
    FILE* file = fopen("sensex_data.txt", "r");
    if (!file) {
        printf("File not found!\n");
        return;
    }

    char line[100];
    fgets(line, 100, file); // skip header

    while (fgets(line, 100, file)) {
        sscanf(line, "%[^,],%f,%f,%f,%f", 
            data[size].date, 
            &data[size].open, 
            &data[size].high, 
            &data[size].low, 
            &data[size].close);
        size++;
    }

    fclose(file);
}
