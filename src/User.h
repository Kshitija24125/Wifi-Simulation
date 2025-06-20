#ifndef USER_H
#define USER_H
#include <vector>
using namespace std;
class User {
private:
    const int packetSize;  
    int id;
    int nextAttemptTime = 0;
    int attemptCount = 0;
    int totalAttempts = 0;
    int successfulTransmissions = 0;  
    double totalTxTime = 0;
    double totalBytes = 0;
    int latency = 0.0;
    double throughput = 0.0;
    double totalOverheadTime = 0.0;     

    vector<double> latencies;
    vector<int> transmissionTimes;
    vector<double> packetGenerationTimes;
    vector<double> packetGenTimes;  


public:
    User(int id, int packetSize = 1024);
    // int successfulTransmissions = 0;  // Add this member variable
    
    // Getters
    int getPacketSize() const { return packetSize; }
    int getId() const { return id; }
    int getLatency() const { return latency; }
    double getThroughput() const { return throughput; }
    double getThroughputMbps() const { return throughput / 1e6; }
    double getAverageLatency() const;
    int getNextAttemptTime() const { return nextAttemptTime; }
    int getAttemptCount() const { return attemptCount; }
    int getTotalAttempts() const { return totalAttempts; }
    int getSuccessfulTransmissions() const {
        return successfulTransmissions;
    }
    // int getSuccessfulTransmissions() const { return successfulTransmissions; }  // Add this getter
    void generatePacket(double currentTime); 
    double getOldestPacketTime() const;   
    void popOldestPacket() {
        if (!packetGenerationTimes.empty()) packetGenerationTimes.erase(packetGenerationTimes.begin());

    }   
     void recordSuccessfulTransmission() {
        successfulTransmissions++;
    }
    void calculateThroughput(double totalSimTimeSec);  
    void recordLatency(double latency);  
    void recordCsiTransmission(int currentTime, int duration);
    void recordParallelTransmission(double startTime, double duration,double latency);
    bool hasDataToSend() const;
    int getPendingDataSize() const;


    void setLatency(int l);
    void setThroughput(double t);
    void setNextAttemptTime(int time) { nextAttemptTime = time; }
    void incrementAttemptCount();
    void resetAttemptCount();
    void incrementSuccessfulTransmissions() { successfulTransmissions++; }  
    
    void transmitData(int packetSizeOverride = 0);
    void recordTransmission(int startTime, int durationMs,int latency);
    void recordOFDMAStats(double startTime, double durationMs, double latency) ;

    // Move operations
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;
    
    // Delete copy operations
    User(const User&) = delete;
    User& operator=(const User&) = delete;
};

#endif