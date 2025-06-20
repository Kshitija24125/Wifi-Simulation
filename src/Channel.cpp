
#include "Channel.h"

Channel::Channel() : totalBandwidth(20), busy(false) {
}


bool Channel::isFree() const { return !busy; }
void Channel::occupy() { busy = true; }
void Channel::release() { busy = false; }
//simulate transmission: Mark the channel as busy for a given duration
void Channel::simulateTransmission(int transmissionDuration) {
    occupy();
    std::this_thread::sleep_for(std::chrono::milliseconds(transmissionDuration));  // Simulate the transmission time
    release();  // Release the channel after transmission is complete
}