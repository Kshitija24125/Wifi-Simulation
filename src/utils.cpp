#include "utils.h"
#include <cstdlib>
#include <ctime>

// Function definitions
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void initializeRandomSeed() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with current time
}

double calculateThroughput(int totalBytes, double timeInSeconds) {
    return (totalBytes * 8) / timeInSeconds; // Convert bytes to bits and calculate throughput
}

int getRandomBackoffTime(int min, int max) {
    return getRandomNumber(min, max);
}