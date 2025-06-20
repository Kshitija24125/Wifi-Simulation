#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <vector>
#include "User.h"
#include "Channel.h"
#include "WiFiSimulation.h"
using namespace std;

class AccessPoint {
public:
    AccessPoint(int numUsers, WiFiSimulation* simulation);
    ~AccessPoint();

    void runSimulation();

    const vector<User>& getUsers() const;
    Channel& getChannel();

private:
    vector<User> users;
    Channel channel;
    WiFiSimulation* simulation;
};

#endif
