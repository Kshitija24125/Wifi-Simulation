
#ifndef WIFI_SIMULATION_H
#define WIFI_SIMULATION_H

#include <vector>
#include "User.h"
#include "Channel.h"

class WiFiSimulation {
public:
    virtual void run(std::vector<User>& users, Channel& channel) = 0;
    virtual ~WiFiSimulation() = default;
};

#endif