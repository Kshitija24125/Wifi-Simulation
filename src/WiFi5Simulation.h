
#ifndef WIFI5SIMULATION_H
#define WIFI5SIMULATION_H

#include "WiFiSimulation.h"
using namespace std;

class WiFi5Simulation : public WiFiSimulation {
public:
    explicit WiFi5Simulation(int duration_ms = 60000.0) : SIM_DURATION(duration_ms){}
    void run(vector<User>& users, Channel& channel) override;
    double calculateTransmissionTime(int packetSizeBytes) const ;

    const double CSI_TIME_PER_USER = 0.012; // 0.012ms per user for CSI feedback

private:

    const double CSI_PACKET_SIZE = 200.0;        
    const double PACKET_SIZE = 1024.0;        
    const double PARALLEL_WINDOW_MS = 15.0;      
    const double BROADCAST_PACKET_SIZE = 100.0;  
    int SIM_DURATION;                      
    const long double BANDWIDTH = 20e6L;        
    const long double MOD_EFFICIENCY = 8.0;     
    const long double CODE_RATE = 5.0/6.0;      
    
    void performChannelSounding(vector<User>& users, Channel& channel, double& currentTime);
    void parallelTransmission(vector<User>& users, double& currentTime);
    void printFinalMetrics(const vector<User>& users) const ;

};

#endif 