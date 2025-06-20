
#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include <vector>
#include <chrono>
#include <thread>
class Channel {
private:
    int totalBandwidth;           // in MHz
    bool busy;

public:
    Channel();


    bool isFree() const;
    void occupy();
    void release();
    void simulateTransmission(int transmissionDuration);  // Simulate transmission and mark the channel as busy for that duration
};

#endif