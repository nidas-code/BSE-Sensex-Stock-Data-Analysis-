#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "data_reader.h"

void showDataOverview(SensexEntry data[], int size);
void calculateAverages(SensexEntry data[], int size);
void detectVolatility(SensexEntry data[], int size, float threshold);
void identifyTrends(SensexEntry data[], int size);
void findLongestIncreasingDecreasing(SensexEntry data[], int size);
void computeSMA(SensexEntry data[], int size, int windowSize);
void detectSupportResistance(SensexEntry data[], int size, int roundingFactor);
void topNClosings(SensexEntry data[], int size, int N);
void bestWorstMonthsYears(SensexEntry data[], int size);


#endif
