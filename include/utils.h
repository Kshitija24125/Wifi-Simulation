#ifndef UTILS_H
#define UTILS_H

// Function declarations (only)
int getRandomNumber(int min, int max);
void initializeRandomSeed();
double calculateThroughput(int totalBytes, double timeInSeconds);
int getRandomBackoffTime(int min, int max);  // Add this line
#endif // UTILS_H
