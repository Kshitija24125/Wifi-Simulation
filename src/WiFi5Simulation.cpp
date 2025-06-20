#include "WiFi5Simulation.h"
#include <iostream>
#include <iomanip>
#include <utils.h>
#include "WiFi4Simulation.h"
#include "User.h"

using namespace std;

double WiFi5Simulation::calculateTransmissionTime(int PACKET_SIZE ) const {

    const  double BANDWIDTH = 20e6;       
    const double MOD_EFFICIENCY = 8.0;   
    const double CODE_RATE = 5.0/6.0;    
    
    double bits = PACKET_SIZE * 8.0;

    double rate = (BANDWIDTH * MOD_EFFICIENCY * CODE_RATE);
    return (bits / rate) *1000.0; // ms
}

void WiFi5Simulation::run(vector<User>& users, Channel& channel) {
    initializeRandomSeed();
    double currentTime = 0.0;
    cout << fixed << setprecision(3);
    cout << "=== WiFi 5 MU-MIMO Simulation ===\n";
    // cout << "PHY Rate: " << (BANDWIDTH * MOD_EFFICIENCY * CODE_RATE / 1e6) << " Mbps (20 MHz, 256-QAM, 5/6 coding)\n\n";

    while (currentTime < SIM_DURATION) {
        // Phase 1: Channel Sounding
        cout << "\n[Cycle Start @ T+" << currentTime << "ms]\n";
        cout << "1. AP Broadcast Phase (" << BROADCAST_PACKET_SIZE << "B)\n";
        for (auto& user : users) {
            user.generatePacket(currentTime);
        }
        performChannelSounding(users, channel, currentTime);
        
        // Phase 2: Parallel Transmission
        cout << "3. Parallel Transmission Phase (15ms window)\n";
        parallelTransmission(users, currentTime);
        cout << "[Cycle End @ T+" << currentTime << "ms]\n";
    }

    double totalSimTimeSec = currentTime / 1000.0;
    for (auto& user : users) {
        user.calculateThroughput(totalSimTimeSec);
    }
    printFinalMetrics(users);
}


void WiFi5Simulation::performChannelSounding(vector<User>& users,  Channel& channel, double& currentTime) {
    // AP Broadcast
    cout << fixed << setprecision(6); 

    channel.occupy();
    double broadcastTime = calculateTransmissionTime(BROADCAST_PACKET_SIZE);
    cout << "   - AP broadcasting for " << broadcastTime << "ms\n";
    currentTime += broadcastTime;
    channel.release();
    
    // CSI Feedback
    cout << "2. Sequential CSI Feedback Phase:\n";

        for (auto& user : users) {
        channel.occupy();
        double csiTime = calculateTransmissionTime(CSI_PACKET_SIZE );
        cout << "   - User " << user.getId() << " (" << CSI_PACKET_SIZE << "B): " << csiTime << "ms\n";
         user.recordCsiTransmission(currentTime, csiTime);
        currentTime += csiTime;
        channel.release();
    }
    cout << "   Total CSI Time: " << currentTime << "ms\n";
}

void WiFi5Simulation::parallelTransmission(vector<User>& users, double& currentTime) {

    double windowEnd = currentTime + PARALLEL_WINDOW_MS;
    int cycleSuccessCount = 0;
    
    for (int i = 0; i < users.size(); i++) {
        if (users[i].hasDataToSend()) {
            double neededTime = calculateTransmissionTime(users[i].getPendingDataSize());
            
            if (neededTime <= PARALLEL_WINDOW_MS) {
                // Successful transmission - record it
                users[i].recordSuccessfulTransmission();
                cycleSuccessCount++;
                
                // Calculate and record latency (ADD THIS PART)
                double latency = (currentTime - users[i].getOldestPacketTime()) 
                              + (i * CSI_TIME_PER_USER);  // CSI sequential delay
                users[i].recordLatency(latency);
                
                // Update throughput calculations
                users[i].recordTransmission(currentTime, neededTime,latency);
            }

        }
    }
     currentTime = windowEnd;
}

void WiFi5Simulation::printFinalMetrics(const vector<User>& users) const {
    double totalThroughput = 0;
    double totalLatency = 0;
    int totalFrames = 0;
    
    cout << "\n=== FINAL METRICS ===\n";
    cout << "User ID | Success TX | Avg Latency | Throughput\n";
    cout << "--------|------------|-------------|-----------\n";
    
    for (const auto& user : users) {
                 cout << setw(7) << user.getId() << " | "
                  << setw(10) << user.getSuccessfulTransmissions() << " | "
                  << setw(11) << user.getAverageLatency() << "ms | "
                  << fixed << setprecision(2) 
                  << setw(9) << user.getThroughputMbps() << " Mbps\n";
        
        totalThroughput += user.getThroughputMbps();
        totalLatency += user.getAverageLatency();
        totalFrames += user.getSuccessfulTransmissions();
    }
    
    cout << "\nNETWORK TOTALS:\n"
         << "- Aggregate Throughput: " << totalThroughput << " Mbps\n"
         << "- Mean Latency: " << totalLatency/users.size() << "ms\n"
         << "- Total Frames Delivered: " << totalFrames << "\n";
}