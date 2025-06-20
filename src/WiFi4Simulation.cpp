
#include "WiFi4Simulation.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <iomanip>  
#include <limits>   
using namespace std; 

int WiFi4Simulation::calculateTransmissionTime() const {
    const long double bits = static_cast<long double>(PACKET_SIZE *8);
    const long double rate = 
        static_cast<long double>(BANDWIDTH) * 
        static_cast<long double>(MOD_EFFICIENCY) * 
        static_cast<long double>(CODE_RATE);
    
    const long double seconds = bits / rate;
    
    const long double ms = seconds * 1000.0L;
    
    // 4. Debug output with full precision
    // std::cout << std::setprecision(15) 
    //           << "CALC: " << bits << "b / " << rate << "bps = " 
    //           << "s = " << ms << "ms\n";
    
    return static_cast<int>(round(ms));
}

int WiFi4Simulation::getExponentialBackoff(int attemptCount) const {
    return (rand() % (1 << min(attemptCount, 5))) + 1;
}

void WiFi4Simulation::run(vector<User>& users, Channel& channel) {

    initializeRandomSeed();
    priority_queue<TransmissionEvent> eventQueue;
    double currentTime = 0;
    int user_id = 1;  
    
    cout << "Simulating WiFi 4 Communication (CSMA/CA)...\n";
    cout << "Packet Size: " << PACKET_SIZE << " bytes\n"<< "Transmission Time: " << calculateTransmissionTime() << "ms\n";

    for (auto& user : users) {
        user = User(user_id++, PACKET_SIZE);
        user.setNextAttemptTime(getRandomBackoffTime(1, 20));
    }
    while (currentTime < SIM_DURATION) {

                if (eventQueue.empty()) {
                    currentTime++;
                } else {
                    currentTime = static_cast<int>(eventQueue.top().endTime);
                    while (!eventQueue.empty() && eventQueue.top().endTime <= currentTime) {
                        auto event = eventQueue.top();
                        channel.release();
                        eventQueue.pop();
                        cout << "User " << event.userId  << " completed transmission at " << currentTime << "ms\n";
                    }
                }

        // Randomize user processing order
        vector<size_t> userOrder(users.size());
        iota(userOrder.begin(), userOrder.end(), 0);
        shuffle(userOrder.begin(), userOrder.end(), default_random_engine(rand()));

        for (auto idx : userOrder) {
            auto& user = users[idx];
            if (user.getNextAttemptTime() <= currentTime) {
                cout << "User " << user.getId() << " is sniffing the channel...\n";
                
                if (channel.isFree()) {
                    cout << "User " << user.getId() << " found the channel free!\n";
                    
                    int txTime = max(1,calculateTransmissionTime());
                    channel.occupy();
                    eventQueue.push(TransmissionEvent{user.getId(), currentTime + (txTime)});
                    
                    int latency = currentTime - user.getNextAttemptTime();
                    user.recordTransmission(currentTime, txTime , latency);
                    user.resetAttemptCount();
                    
                    cout << "User " << user.getId()   << " starts transmission at " << currentTime << "ms" << " for " << (txTime) << "ms\n";
                } else {
                    cout << "User " << user.getId() << " found the channel busy!\n";
                    
                    int backoff = getExponentialBackoff(user.getAttemptCount());
                    user.incrementAttemptCount();
                    user.setNextAttemptTime(currentTime + backoff);
                    
                    cout << "User " << user.getId()  << " backs off for " << backoff << "ms at "  << currentTime << "ms\n";
                }
            }
        }

        // Advance time
        currentTime = eventQueue.empty() ? currentTime + 1 : min(eventQueue.top().endTime, static_cast<double>(currentTime + 1));
    }


    saveResults(users);
    printFinalMetrics(users); 
}

void WiFi4Simulation::saveResults(const vector<User>& users) const {
    ofstream outFile("wifi4_results.csv");
    if (outFile.is_open()) {
        outFile << "UserID,AvgLatency(ms),Throughput(Mbps),Attempts\n";
        for (const auto& user : users) {
            outFile << user.getId() << ","
                    << user.getAverageLatency() << ","
                    << user.getThroughputMbps() << ","
                    << user.getTotalAttempts() << "\n";
        }
        outFile.close();
        cout << "Results saved to wifi4_results.csv\n";
    } else {
        cerr << "Error writing to wifi4_results.csv\n";
    }
}
void WiFi4Simulation::printFinalMetrics(const vector<User>& users) const {
    double totalThroughput = 0;
    double totalLatency = 0;
    int totalAttempts = 0;
    int successfulTx = 0;
    
    cout << "\n=== Simulation Results ===\n";
    for (const auto& user : users) {
        double successRate = user.getTotalAttempts() > 0 ? 
            (100.0 * user.getSuccessfulTransmissions() / user.getTotalAttempts()) : 0;
        
        cout << "User " << user.getId() << ":\n"
                  << "  Latency: " << user.getAverageLatency() << "ms\n"
                  << "  Throughput: " << user.getThroughputMbps() << " Mbps\n"
                  << "  Success Rate: " << successRate << "%\n";
        
        totalThroughput += user.getThroughputMbps();
        totalLatency += user.getAverageLatency();
        totalAttempts += user.getTotalAttempts();
        successfulTx += user.getSuccessfulTransmissions();
    }
    
    cout << "\nNetwork Summary:\n"
              << "  Avg Latency: " << totalLatency/users.size() << "ms\n"
              << "  Total Throughput: " << totalThroughput << " Mbps\n"
              << "  Success Rate: " << (100.0 * successfulTx/totalAttempts) << "%\n"
              << "  Collision Rate: " << (100.0 * (totalAttempts-successfulTx)/totalAttempts) << "%\n";
}