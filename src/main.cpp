#include <iostream>
#include "Scheduler.hpp"
using namespace std;

int main() {
     cout << "====================================================\n";
     cout << "   AIR TRAFFIC CONTROL DYNAMIC RUNWAY SCHEDULER    \n";
     cout << "====================================================\n\n";

    // 3-minute safety separation interval between runway operations
    Scheduler atc(3);

    // Register active runways
    atc.addRunway({1, "09L", RunwayStatus::IDLE, 0});
    atc.addRunway({2, "27R", RunwayStatus::IDLE, 0});

    // Inject incoming traffic with varied conditions
     cout << "[INIT] Queueing scheduled and emergency aircraft...\n";
    atc.submitFlight({"AI-101", FlightType::ARRIVAL,   90, EmergencyLevel::NONE,             0});
    atc.submitFlight({"6E-204", FlightType::ARRIVAL,   12, EmergencyLevel::LOW_FUEL,         1});
    atc.submitFlight({"SG-512", FlightType::DEPARTURE, 150, EmergencyLevel::NONE,            0});
    atc.submitFlight({"UK-880", FlightType::ARRIVAL,    8, EmergencyLevel::CRITICAL_FAILURE, 2});
    atc.submitFlight({"QP-331", FlightType::ARRIVAL,   40, EmergencyLevel::NONE,             2});
     cout << "\n--- SIMULATION DISPATCH LOG ---\n";

    // Advance discrete simulation clock from T=0 to T=10 minutes
    for (int minute = 0; minute <= 10; ++minute) {
        atc.tick(minute);
    }

     cout << "\n====================================================\n";
     cout << "Simulation completed. Total operations dispatched: " 
              << atc.getHistory().size() << "\n";
     cout << "Pending flights awaiting slot: " 
              << atc.getPendingFlightCount() << "\n";
     cout << "====================================================\n";

    return 0;
}