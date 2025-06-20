#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size;          // in bytes
    int creationTime;  // in ms

public:
    Packet(int size = 1024, int creationTime = 0);

    int getSize() const;
    void setSize(int s);

    int getCreationTime() const;
    void setCreationTime(int t);
};

#endif
