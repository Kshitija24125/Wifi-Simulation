#include "Packet.h"

Packet::Packet(int size, int creationTime)
    : size(size), creationTime(creationTime) {}

int Packet::getSize() const {
    return size;
}

void Packet::setSize(int s) {
    size = s;
}

int Packet::getCreationTime() const {
    return creationTime;
}

void Packet::setCreationTime(int t) {
    creationTime = t;
}
