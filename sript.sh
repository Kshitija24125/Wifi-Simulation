# #!/bin/bash     

# BASE_DIR="WiFi_Simulation_Project"


# mkdir -p $BASE_DIR/simulations
# mkdir -p $BASE_DIR/core
# mkdir -p $BASE_DIR/utils
# mkdir -p $BASE_DIR/results
# mkdir -p $BASE_DIR/resources

# mv main.cpp $BASE_DIR/
# mv WiFiSimulation.h $BASE_DIR/simulations/
# mv WiFiSimulation.cpp $BASE_DIR/simulations/
# mv WiFi4Simulation.h $BASE_DIR/simulations/
# mv WiFi4Simulation.cpp $BASE_DIR/simulations/
# mv WiFi5Simulation.h $BASE_DIR/simulations/
# mv WiFi5Simulation.cpp $BASE_DIR/simulations/
# mv WiFi6Simulation.h $BASE_DIR/simulations/
# mv WiFi6Simulation.cpp $BASE_DIR/simulations/
# mv User.h $BASE_DIR/core/
# mv User.cpp $BASE_DIR/core/
# mv Packet.h $BASE_DIR/core/
# mv Packet.cpp $BASE_DIR/core/
# mv Channel.h $BASE_DIR/core/
# mv Channel.cpp $BASE_DIR/core/
# mv AccessPoint.h $BASE_DIR/core/
# mv AccessPoint.cpp $BASE_DIR/core/
# mv utils.h $BASE_DIR/utils/
# mv plot.h $BASE_DIR/utils/
# mv plot.cpp $BASE_DIR/utils/
# mv GraphRenderer.h $BASE_DIR/utils/
# mv GraphRenderer.cpp $BASE_DIR/utils/


# touch $BASE_DIR/results/.gitkeep
# touch $BASE_DIR/resources/.gitkeep

# echo "File structure created successfully in $BASE_DIR/"



#!/bin/bash

BASE_DIR="WiFi_Simulation_Project"

mkdir -p $BASE_DIR/simulations
mkdir -p $BASE_DIR/core
mkdir -p $BASE_DIR/utils
mkdir -p $BASE_DIR/results
mkdir -p $BASE_DIR/resources

cd $BASE_DIR

touch simulations/WiFiSimulation.h
touch simulations/WiFiSimulation.cpp
touch simulations/WiFi4Simulation.h
touch simulations/WiFi4Simulation.cpp
touch simulations/WiFi5Simulation.h
touch simulations/WiFi5Simulation.cpp
touch simulations/WiFi6Simulation.h
touch simulations/WiFi6Simulation.cpp

touch core/User.h
touch core/User.cpp
touch core/Packet.h
touch core/Packet.cpp
touch core/Channel.h
touch core/Channel.cpp
touch core/AccessPoint.h
touch core/AccessPoint.cpp

touch utils/utils.h
touch utils/plot.h
touch utils/plot.cpp
touch utils/GraphRenderer.h
touch utils/GraphRenderer.cpp

touch main.cpp

touch results/.gitkeep
touch resources/.gitkeep

echo "File structure created successfully in $BASE_DIR/"