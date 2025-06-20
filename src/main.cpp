#include <iostream>
#include "WiFi4Simulation.h"
#include "WiFi5Simulation.h"
#include "WiFi6Simulation.h"
#include "AccessPoint.h"

using namespace std;

int main() {
    try {
        int numberOfUsers;
        cout << "Enter the number of users: ";
        cin >> numberOfUsers;

        if (numberOfUsers <= 0) {
            cerr << "Number of users must be greater than 0. Exiting program." << endl;
            return 1;
        }

        bool running = true;

        while (running) {
            cout << "\nSelect the WiFi simulation to run:\n";
            cout << "1. WiFi 4 (CSMA/CA)\n";
            cout << "2. WiFi 5 (MU-MIMO)\n";
            cout << "3. WiFi 6 (OFDMA)\n";
            cout << "4. Exit\n";
            cout << "Enter your choice (1-4): ";

            int choice;
            cin >> choice;

            if (choice == 4) {
                cout << "Exiting program. Goodbye!" << endl;
                break;
            }

            WiFiSimulation* sim = nullptr;

            switch (choice) {
                case 1:
                    sim = new WiFi4Simulation();
                    break;
                case 2:
                    sim = new WiFi5Simulation();
                    break;
                case 3:
                    sim = new WiFi6Simulation();
                    break;
                default:
                    cerr << "Invalid choice! Please select a valid option." << endl;
                    continue; // Skip to next loop iteration
            }

            AccessPoint ap(numberOfUsers, sim);
            ap.runSimulation(); // Uses polymorphic run()
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
