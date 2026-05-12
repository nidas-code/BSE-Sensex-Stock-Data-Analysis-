#include <cstdio>
#include "analysis.h"

void showDataOverview(SensexEntry data[], int size) {
    printf("Total Entries: %d\n", size);
    printf("First Entry: %s\n", data[0].date);
    printf("Last Entry: %s\n", data[size - 1].date);
    
    float minClose = data[0].close, maxClose = data[0].close;
    for (int i = 1; i < size; ++i) {
        if (data[i].close < minClose) minClose = data[i].close;
        if (data[i].close > maxClose) maxClose = data[i].close;
    }
    printf("Min Close: %.2f\n", minClose);
    printf("Max Close: %.2f\n", maxClose);
}
#include <cstring>  // for strcmp, strncpy

void calculateAverages(SensexEntry data[], int size) {
    // Temporary arrays to hold monthly and yearly totals
    char currentMonth[8];  // format: YYYY-MM
    char currentYear[5];   // format: YYYY

    float monthlyTotal = 0;
    int monthlyCount = 0;

    float yearlyTotal = 0;
    int yearlyCount = 0;

    printf("\n--- Monthly Averages ---\n");

    strncpy(currentMonth, data[0].date, 7);
    currentMonth[7] = '\0';

    strncpy(currentYear, data[0].date, 4);
    currentYear[4] = '\0';

    for (int i = 0; i < size; ++i) {
        char thisMonth[8];
        char thisYear[5];

        strncpy(thisMonth, data[i].date, 7);
        thisMonth[7] = '\0';

        strncpy(thisYear, data[i].date, 4);
        thisYear[4] = '\0';

        if (strcmp(thisMonth, currentMonth) != 0) {
            float monthlyAvg = monthlyTotal / monthlyCount;
            printf("Month: %s, Average Close: %.2f\n", currentMonth, monthlyAvg);
            strncpy(currentMonth, thisMonth, 8);
            monthlyTotal = 0;
            monthlyCount = 0;
        }

        if (strcmp(thisYear, currentYear) != 0) {
            float yearlyAvg = yearlyTotal / yearlyCount;
            printf("Year: %s, Average Close: %.2f\n", currentYear, yearlyAvg);
            strncpy(currentYear, thisYear, 5);
            yearlyTotal = 0;
            yearlyCount = 0;
        }

        monthlyTotal += data[i].close;
        monthlyCount++;

        yearlyTotal += data[i].close;
        yearlyCount++;
    }

    // Print final month/year
    float finalMonthlyAvg = monthlyTotal / monthlyCount;
    printf("Month: %s, Average Close: %.2f\n", currentMonth, finalMonthlyAvg);

    float finalYearlyAvg = yearlyTotal / yearlyCount;
    printf("Year: %s, Average Close: %.2f\n", currentYear, finalYearlyAvg);
}
void detectVolatility(SensexEntry data[], int size, float threshold) {
    printf("\n--- High Volatility Days (>%0.2f%%) ---\n", threshold);
    int count = 0;

    for (int i = 0; i < size; ++i) {
        float volatility = ((data[i].high - data[i].low) / data[i].open) * 100.0;

        if (volatility > threshold) {
            printf("%s | Open: %.2f | High: %.2f | Low: %.2f | Close: %.2f | Volatility: %.2f%%\n",
                   data[i].date, data[i].open, data[i].high, data[i].low, data[i].close, volatility);
            count++;
        }
    }

    printf("Total high volatility days: %d\n", count);
}
void identifyTrends(SensexEntry data[], int size) {
    int currentBullStart = 0, currentBullLength = 1;
    int maxBullStart = 0, maxBullLength = 1;

    int currentBearStart = 0, currentBearLength = 1;
    int maxBearStart = 0, maxBearLength = 1;

    for (int i = 1; i < size; ++i) {
        // Bullish: increasing close
        if (data[i].close > data[i - 1].close) {
            currentBullLength++;
        } else {
            if (currentBullLength > maxBullLength) {
                maxBullLength = currentBullLength;
                maxBullStart = i - currentBullLength;
            }
            currentBullLength = 1;
        }

        // Bearish: decreasing close
        if (data[i].close < data[i - 1].close) {
            currentBearLength++;
        } else {
            if (currentBearLength > maxBearLength) {
                maxBearLength = currentBearLength;
                maxBearStart = i - currentBearLength;
            }
            currentBearLength = 1;
        }
    }

    // Final check at end of data
    if (currentBullLength > maxBullLength) {
        maxBullLength = currentBullLength;
        maxBullStart = size - currentBullLength;
    }
    if (currentBearLength > maxBearLength) {
        maxBearLength = currentBearLength;
        maxBearStart = size - currentBearLength;
    }

    printf("\n--- Trend Identification ---\n");
    printf("Longest Bullish Run: %d days (from %s to %s)\n",
           maxBullLength, data[maxBullStart].date, data[maxBullStart + maxBullLength - 1].date);
    printf("Longest Bearish Run: %d days (from %s to %s)\n",
           maxBearLength, data[maxBearStart].date, data[maxBearStart + maxBearLength - 1].date);
}
int maxIndex(int arr[], int n) {
    int maxVal = arr[0], maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIdx = i;
        }
    }
    return maxIdx;
}

void findLongestIncreasingDecreasing(SensexEntry data[], int size) {
    int LIS[size];
    int LDS[size];

    for (int i = 0; i < size; ++i) {
        LIS[i] = 1;
        LDS[i] = 1;
    }

    // Build LIS
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            if (data[i].close > data[j].close && LIS[i] < LIS[j] + 1) {
                LIS[i] = LIS[j] + 1;
            }
            if (data[i].close < data[j].close && LDS[i] < LDS[j] + 1) {
                LDS[i] = LDS[j] + 1;
            }
        }
    }

    int lisEnd = maxIndex(LIS, size);
    int ldsEnd = maxIndex(LDS, size);

    printf("\n--- Longest Increasing/Decreasing Subsequences ---\n");
    printf("Longest Increasing Subsequence: %d days, ends at %s (Close = %.2f)\n",
           LIS[lisEnd], data[lisEnd].date, data[lisEnd].close);
    printf("Longest Decreasing Subsequence: %d days, ends at %s (Close = %.2f)\n",
           LDS[ldsEnd], data[ldsEnd].date, data[ldsEnd].close);
}
void computeSMA(SensexEntry data[], int size, int windowSize) {
    if (windowSize <= 0 || windowSize > size) {
        printf("Invalid window size!\n");
        return;
    }

    printf("\n--- Simple Moving Average (Window = %d) ---\n", windowSize);

    for (int i = windowSize - 1; i < size; ++i) {
        float sum = 0;
        for (int j = i - windowSize + 1; j <= i; ++j) {
            sum += data[j].close;
        }
        float sma = sum / windowSize;
        printf("Date: %s | SMA: %.2f\n", data[i].date, sma);
    }
}
void detectSupportResistance(SensexEntry data[], int size, int roundingFactor) {
    const int MAX_LEVELS = 1000;
    int levels[MAX_LEVELS] = {0};
    int values[MAX_LEVELS] = {0};
    int uniqueCount = 0;

    for (int i = 0; i < size; ++i) {
        int level = (int)(data[i].close / roundingFactor) * roundingFactor;

        int found = 0;
        for (int j = 0; j < uniqueCount; ++j) {
            if (values[j] == level) {
                levels[j]++;
                found = 1;
                break;
            }
        }

        if (!found && uniqueCount < MAX_LEVELS) {
            values[uniqueCount] = level;
            levels[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // Sort by frequency (simple selection sort for demo purposes)
    for (int i = 0; i < uniqueCount - 1; ++i) {
        for (int j = i + 1; j < uniqueCount; ++j) {
            if (levels[j] > levels[i]) {
                int tempLevel = levels[i];
                int tempValue = values[i];
                levels[i] = levels[j];
                values[i] = values[j];
                levels[j] = tempLevel;
                values[j] = tempValue;
            }
        }
    }

    printf("\n--- Top 5 Frequent Price Levels (Support/Resistance) ---\n");
    for (int i = 0; i < 5 && i < uniqueCount; ++i) {
        printf("Level: %d | Occurrences: %d\n", values[i], levels[i]);
    }
}
void topNClosings(SensexEntry data[], int size, int N) {
    if (N <= 0 || N > size) {
        printf("Invalid N value!\n");
        return;
    }

    // Make two copies of data for sorting
    SensexEntry highCopy[size];
    SensexEntry lowCopy[size];

    for (int i = 0; i < size; ++i) {
        highCopy[i] = data[i];
        lowCopy[i] = data[i];
    }

    // Sort descending for highest closings
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (highCopy[j].close > highCopy[i].close) {
                SensexEntry temp = highCopy[i];
                highCopy[i] = highCopy[j];
                highCopy[j] = temp;
            }
        }
    }

    // Sort ascending for lowest closings
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (lowCopy[j].close < lowCopy[i].close) {
                SensexEntry temp = lowCopy[i];
                lowCopy[i] = lowCopy[j];
                lowCopy[j] = temp;
            }
        }
    }

    printf("\n--- Top %d Highest Closing Days ---\n", N);
    for (int i = 0; i < N; ++i) {
        printf("Date: %s | Close: %.2f\n", highCopy[i].date, highCopy[i].close);
    }

    printf("\n--- Top %d Lowest Closing Days ---\n", N);
    for (int i = 0; i < N; ++i) {
        printf("Date: %s | Close: %.2f\n", lowCopy[i].date, lowCopy[i].close);
    }
}
#include <cstring>

struct GroupStat {
    char label[10]; // MM-YYYY or YYYY
    float totalClose;
    int count;
};

void bestWorstMonthsYears(SensexEntry data[], int size) {
    GroupStat months[300]; int mCount = 0;
    GroupStat years[100];  int yCount = 0;

    for (int i = 0; i < size; ++i) {
        char month[8], year[5];
        strncpy(year, data[i].date, 4);
        year[4] = '\0';
        strncpy(month, data[i].date + 5, 2);
        month[2] = '\0';

        char monthYear[10];
        sprintf(monthYear, "%s-%s", month, year);

        // Month-level grouping
        int foundMonth = 0;
        for (int j = 0; j < mCount; ++j) {
            if (strcmp(months[j].label, monthYear) == 0) {
                months[j].totalClose += data[i].close;
                months[j].count++;
                foundMonth = 1;
                break;
            }
        }
        if (!foundMonth) {
            strcpy(months[mCount].label, monthYear);
            months[mCount].totalClose = data[i].close;
            months[mCount].count = 1;
            mCount++;
        }

        // Year-level grouping
        int foundYear = 0;
        for (int j = 0; j < yCount; ++j) {
            if (strcmp(years[j].label, year) == 0) {
                years[j].totalClose += data[i].close;
                years[j].count++;
                foundYear = 1;
                break;
            }
        }
        if (!foundYear) {
            strcpy(years[yCount].label, year);
            years[yCount].totalClose = data[i].close;
            years[yCount].count = 1;
            yCount++;
        }
    }

    // Find best/worst months
    float bestMonthAvg = -1, worstMonthAvg = 1e9;
    char bestMonth[10], worstMonth[10];

    for (int i = 0; i < mCount; ++i) {
        float avg = months[i].totalClose / months[i].count;
        if (avg > bestMonthAvg) {
            bestMonthAvg = avg;
            strcpy(bestMonth, months[i].label);
        }
        if (avg < worstMonthAvg) {
            worstMonthAvg = avg;
            strcpy(worstMonth, months[i].label);
        }
    }

    // Find best/worst years
    float bestYearAvg = -1, worstYearAvg = 1e9;
    char bestYear[10], worstYear[10];

    for (int i = 0; i < yCount; ++i) {
        float avg = years[i].totalClose / years[i].count;
        if (avg > bestYearAvg) {
            bestYearAvg = avg;
            strcpy(bestYear, years[i].label);
        }
        if (avg < worstYearAvg) {
            worstYearAvg = avg;
            strcpy(worstYear, years[i].label);
        }
    }

    printf("\n--- Best/Worst Months and Years ---\n");
    printf("Best Month : %s | Avg Close: %.2f\n", bestMonth, bestMonthAvg);
    printf("Worst Month: %s | Avg Close: %.2f\n", worstMonth, worstMonthAvg);
    printf("Best Year  : %s | Avg Close: %.2f\n", bestYear, bestYearAvg);
    printf("Worst Year : %s | Avg Close: %.2f\n", worstYear, worstYearAvg);
}




