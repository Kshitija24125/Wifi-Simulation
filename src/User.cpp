#include "User.h"
#include <numeric> 

User::User(int id, int packetSize) 
    : packetSize(packetSize), id(id) {}

// Move constructor
User::User(User&& other) noexcept 
    : packetSize(other.packetSize),
      id(other.id),
      nextAttemptTime(other.nextAttemptTime),
      attemptCount(other.attemptCount),
      totalAttempts(other.totalAttempts),
      successfulTransmissions(other.successfulTransmissions),  // Add this line
      latencies(std::move(other.latencies)),
      totalBytes(other.totalBytes),
      totalTxTime(other.totalTxTime),
      latency(other.latency),
      throughput(other.throughput) {}

// Move assignment
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        // packetSize and id are const - can't be assigned
        nextAttemptTime = other.nextAttemptTime;
        attemptCount = other.attemptCount;
        totalAttempts = other.totalAttempts;
        successfulTransmissions = other.successfulTransmissions;  // Add this line
        latencies = std::move(other.latencies);
        totalBytes = other.totalBytes;
        totalTxTime = other.totalTxTime;
        latency = other.latency;
        throughput = other.throughput;
    }
    return *this;
}

double User::getAverageLatency() const {
    if (latencies.empty()) return 0;
    return std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
}

void User::setLatency(int l) { 
    latency = l;
    if (latencies.empty()) {
        latencies.push_back(l);
    } else {
        latencies.back() = l;
    }
}

void User::setThroughput(double t) { 
    throughput = t;
}


void User::incrementAttemptCount() { 
    attemptCount++; 
    totalAttempts++;
}

void User::resetAttemptCount() { 
    attemptCount = 0; 
}

void User::transmitData(int packetSizeOverride) {
    int effectiveSize = packetSizeOverride ? packetSizeOverride : packetSize;
    double bits = effectiveSize * 8.0;
    double rate = 20e6 * 8 * (5.0/6.0); 
    double seconds = bits / rate;
    int transmissionTime = static_cast<int>(seconds * 1000);
    transmissionTime = std::max(1, transmissionTime); 
    
    setLatency(transmissionTime);
    totalBytes += effectiveSize;
    totalTxTime += transmissionTime / 1000.0;
    throughput = (totalBytes * 8) / totalTxTime;
}

    void User::recordTransmission(int startTime, int durationMs, int measuredLatency) {
    latencies.push_back(measuredLatency);    
    totalBytes += packetSize;
    totalTxTime += (durationMs / 1000.0);
    throughput = (totalBytes * 8) / totalTxTime;
    successfulTransmissions++;
}

void User::recordCsiTransmission(int currentTime, int duration) {
    transmissionTimes.push_back(currentTime);
}

void User::recordParallelTransmission(double startTime, double duration,double latency) {
    transmissionTimes.push_back(startTime);
    latencies.push_back(latency);
    totalBytes += packetSize;
    totalTxTime += (duration / 1000.0);
    throughput = (totalBytes * 8) / totalTxTime;
}

bool User::hasDataToSend() const {
    return true;
}

int User::getPendingDataSize() const {
    return packetSize;
}
void User::generatePacket(double currentTime) {
    packetGenerationTimes.push_back(currentTime);
}

double User::getOldestPacketTime() const {
    if (packetGenerationTimes.empty()) return 0;
    return packetGenerationTimes.front();
}
void User::calculateThroughput(double totalSimTimeSec) {
    throughput = ((successfulTransmissions * packetSize * 8) / totalSimTimeSec) ;
}
void User::recordLatency(double latency) {
    latencies.push_back(latency);  
}
void User:: recordOFDMAStats(double startTime, double durationMs, double latency) {
    transmissionTimes.push_back(startTime);
    latencies.push_back(latency);
    totalBytes += packetSize;
    totalTxTime += durationMs / 1000.0;
    throughput = (totalBytes * 8) / totalTxTime;
    successfulTransmissions++;
}
