
#ifndef WIFI6SIMULATION_H
#define WIFI6SIMULATION_H

#include "WiFiSimulation.h"
#include <vector>

using namespace std;

class WiFi6Simulation : public WiFiSimulation {
public:

    int SIM_DURATION;
    explicit WiFi6Simulation(int duration_ms = 100.0) : SIM_DURATION(duration_ms){}
    void run(vector<User>& users, Channel& channel) override;

private:
    
    const vector<int> RU_SIZES = {2, 4, 10};
    const double OFDMA_WINDOW_MS = 5.0;           
    const double TOTAL_BANDWIDTH = 20.0;          
    const double MOD_EFFICIENCY = 8.0;     
    const double CODE_RATE = 5.0 / 6.0;

    struct ResourceUnit {
        int userId;
        double bandwidth; 
    };
    
    vector<ResourceUnit> allocateRUsRoundRobin(vector<User>& users);
    void printFinalMetrics(const vector<User>& users) const;
     

    
};
#endif