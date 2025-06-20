
#ifndef WIFI4SIMULATION_H
#define WIFI4SIMULATION_H

#include "WiFiSimulation.h"
#include <queue>
#include <vector>

using namespace std;

class WiFi4Simulation : public WiFiSimulation {
public:
    void run(vector<User>& users, Channel& channel) override;

private:
    // Transmission event structure
    struct TransmissionEvent {

        int userId;
        double endTime;
        bool operator<(const TransmissionEvent& other) const {
            return endTime > other.endTime; // Min-heap priority queue
        }
    };

    static constexpr int PACKET_SIZE = 1024;       
    static constexpr long double BANDWIDTH = 20000000.0L;      // 20 MHz
    static constexpr long double MOD_EFFICIENCY = 8.0L;  // 256-QAM
    static constexpr long double CODE_RATE = 5.0L/6.0L;   // Coding rate
    static constexpr int MAX_BACKOFF = 20;         // ms
    static constexpr int SIM_DURATION = 10000;     // 10 second simulation

    // Helper methods
    int calculateTransmissionTime() const;
    int getExponentialBackoff(int attemptCount) const;
    void saveResults(const vector<User>& users) const;
    void printFinalMetrics(const vector<User>& users) const ;

};

#endif