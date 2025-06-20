#include "WiFi6Simulation.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

vector<WiFi6Simulation::ResourceUnit> WiFi6Simulation::allocateRUsRoundRobin(vector<User>& users) {
    vector<ResourceUnit> rus;
    double remainingBW = TOTAL_BANDWIDTH;
    static int userIndex = 0;

    // Shuffle RU sizes to simulate dynamic allocation
    vector<int> shuffledRUs = RU_SIZES;
    shuffle(shuffledRUs.begin(), shuffledRUs.end(), mt19937{random_device{}()});

    while (remainingBW > 0 && !users.empty()) {
        for (auto size : shuffledRUs) {
            if (size <= remainingBW) {
                const User& user = users[userIndex % users.size()];
                rus.push_back({user.getId(), static_cast<double>(size)});
                remainingBW -= size;
                userIndex++;
                break;
            }
        }
    }
    return rus;
}

void WiFi6Simulation::run(vector<User>& users, Channel& channel) {
    double currentTime = 0.0;
    cout << "=== WiFi 6 OFDMA Simulation ===\n";
    cout << "Config: 256-QAM, 20MHz total, RU Sizes = {10, 4, 2} MHz, 5ms rounds\n\n";

    while (currentTime < SIM_DURATION) {
        // Step 1: Simulate packet generation
        for (auto& user : users) {
            user.generatePacket(currentTime);
        }

        // Step 2: Allocate RUs to users
        auto rus = allocateRUsRoundRobin(users);
        cout << "[T+" << currentTime << "ms] Allocated: ";
        for (const auto& ru : rus)
        cout << ru.bandwidth << "MHz(U" << ru.userId << ") ";
        cout << "\n";

        // Step 3: Simulate transmission
        for (const auto& ru : rus) {
            auto it = find_if(users.begin(), users.end(), [&](const User& u) {
                return u.getId() == ru.userId;
            });

            if (it != users.end()) {
                User& user = *it;

                // Record transmission and latency
                double latency = currentTime - user.getOldestPacketTime();
                user.recordOFDMAStats(currentTime, OFDMA_WINDOW_MS, latency);
                user.popOldestPacket();

                // Calculate PHY rate based on RU bandwidth
                double rate_bps = ru.bandwidth * 1e6 * MOD_EFFICIENCY * CODE_RATE;
                double throughput = (user.getPacketSize() * 8.0) / (OFDMA_WINDOW_MS / 1000.0); // bps
                user.setThroughput(throughput);
            }
        }

        currentTime += OFDMA_WINDOW_MS;
    }

    // Calculate average throughput over entire simulation
    double simTimeSec = currentTime / 1000.0;
    for (auto& user : users) {
        user.calculateThroughput(simTimeSec);
    }

    printFinalMetrics(users);
}

void WiFi6Simulation::printFinalMetrics(const vector<User>& users) const {
    cout << "\n=== FINAL METRICS ===\n";
    cout << "User ID | Success TX | Avg Latency | Throughput\n";
    cout << "--------|------------|-------------|-----------\n";

    double totalThroughput = 0;
    double totalLatency = 0;
    int totalTx = 0;

    for (const auto& user : users) {
        double avgLat = user.getAverageLatency();
        double mbps = user.getThroughputMbps();
        int txCount = user.getSuccessfulTransmissions();

        cout << setw(7) << user.getId() << " | "
             << setw(10) << txCount << " | "
             << setw(11) << fixed << setprecision(2) << avgLat << " ms | "
             << setw(9) << fixed << setprecision(2) << mbps << " Mbps\n";

        totalThroughput += mbps;
        totalLatency += avgLat;
        totalTx += txCount;
    }

    cout << "\nNETWORK TOTALS:\n";
    cout << "- Aggregate Throughput: " << fixed << setprecision(2) << totalThroughput << " Mbps\n";
    cout << "- Mean Latency: " << (users.empty() ? 0 : totalLatency / users.size()) << " ms\n";
    cout << "- Total Frames Delivered: " << totalTx << "\n";
}
