#include "AccessPoint.h"
#include <stdexcept>
#include <iostream>
using namespace std;

AccessPoint::AccessPoint(int numUsers, WiFiSimulation* sim)
    : simulation(sim) {
    if (numUsers <= 0) {
        throw invalid_argument("Number of users must be positive.");
    }
    users.reserve(numUsers);
    for (int i = 0; i < numUsers; ++i) {
        users.emplace_back(i + 1, 1024); // Or use your PACKET_SIZE constant
    }
}

AccessPoint::~AccessPoint() {
    delete simulation; // Clean up
}

void AccessPoint::runSimulation() {
    try {
        simulation->run(users, channel);
    } catch (const std::exception& e) {
        cerr << "Simulation error: " << e.what() << std::endl;
    }
}

const vector<User>& AccessPoint::getUsers() const {
    return users;
}

Channel& AccessPoint::getChannel() {
    return channel;
}
