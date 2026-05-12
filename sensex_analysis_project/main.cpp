#include <cstdio>
#include "data_reader.h"
#include "analysis.h"

int main() {
    SensexEntry data[10000];
    int size = 0;

    loadData(data, size);

    int choice;
    do {
        printf("\n--- Sensex Data Analysis ---\n");
        printf("1. Data Overview\n");
        printf("2. Calculate Average");
        printf("3. Detect Volatility\n");
        printf("4. Identify Trends (Bullish/Bearish Runs)\n");
        printf("5. Longest Increasing/Decreasing Subsequence\n");
        printf("6. Compute Simple Moving Average (SMA)\n");
        printf("7. Detect Support and Resistance Levels\n");
        printf("8. Top-N Highest/Lowest Closing Days\n");
        printf("9. Best/Worst Months or Years\n");
        printf("10. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
    case 1:
        showDataOverview(data, size);
        break;
    case 2:
        calculateAverages(data, size);
        break;
    case 3:
        float threshold;
        printf("Enter volatility threshold (e.g. 2.5 for 2.5%%): ");
        scanf("%f", &threshold);
        detectVolatility(data, size, threshold);
        break;
    case 4:
    identifyTrends(data, size);
    break;
    case 5:
    findLongestIncreasingDecreasing(data, size);
    break;
    case 6:
    int windowSize;
    printf("Enter window size for SMA: ");
    scanf("%d", &windowSize);
    computeSMA(data, size, windowSize);
    break;
    case 7:
    int roundFactor;
    printf("Enter rounding factor (e.g., 100): ");
    scanf("%d", &roundFactor);
    detectSupportResistance(data, size, roundFactor);
    break;
    case 8:
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    topNClosings(data, size, N);
    break;
    case 9:
    bestWorstMonthsYears(data, size);
    break;


    default:
        printf("Invalid choice.\n");
}

    } while (choice != 10);

    return 0;
}
