# # Compiler and Flags
# CXX = g++
# CXXFLAGS = -std=c++17 -Wall -I/usr/include -I/usr/local/include
# LDFLAGS = -L/usr/lib -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

# # Source Files and Object Files
# SRC = src/AccessPoint.cpp src/Channel.cpp src/main.cpp src/Packet.cpp src/User.cpp \
#       src/WiFi4Simulation.cpp src/WiFi5Simulation.cpp src/WiFi6Simulation.cpp 
# OBJS = $(SRC:.cpp=.o)

# # Targets
# TARGET = WIFIMODULATION

# # Build Types
# all: debug optimized

# # Debug Build
# debug: $(OBJS)
# 	$(CXX) $(CXXFLAGS) -g -o $(TARGET)_debug $(OBJS) $(LDFLAGS)

# # Optimized Build
# optimized: $(OBJS)
# 	$(CXX) $(CXXFLAGS) -O3 -o $(TARGET)_optimized $(OBJS) $(LDFLAGS)

# # Object File Rule
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean Rule
# clean:
# 	rm -f $(OBJS) $(TARGET)_debug $(TARGET)_optimized results.csv results.png
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include -I./src  # Add -I./include to include the 'include' directory
LDFLAGS = -L/usr/lib -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/AccessPoint.cpp src/Channel.cpp src/main.cpp src/Packet.cpp src/User.cpp \
      src/WiFi4Simulation.cpp src/WiFi5Simulation.cpp src/WiFi6Simulation.cpp \
      src/utils.cpp   # Add this line to include utils.cpp

OBJS = $(SRC:.cpp=.o)

# Targets
TARGET = WIFIMODULATION

# Build Types
all: debug optimized

# Debug Build
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) -g -o $(TARGET)_debug $(OBJS) $(LDFLAGS)

# Optimized Build
optimized: $(OBJS)
	$(CXX) $(CXXFLAGS) -O3 -o $(TARGET)_optimized $(OBJS) $(LDFLAGS)

# Object File Rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -f $(OBJS) $(TARGET)_debug $(TARGET)_optimized results.csv results.png
