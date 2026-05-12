#ifndef DATA_READER_H
#define DATA_READER_H

struct SensexEntry {
    char date[15];
    float open, high, low, close;
};

void loadData(SensexEntry data[], int &size);

#endif
