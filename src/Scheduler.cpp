#include "Scheduler.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

Scheduler::Scheduler(int separationIntervalMinutes)
    : separationInterval(separationIntervalMinutes) {}

void Scheduler::addRunway(Runway runway) {
    runways.push_back(move(runway));
}

void Scheduler::submitFlight(const Aircraft& aircraft) {
    pendingQueue.push(aircraft);
}

Runway* Scheduler::findOptimalRunway(int currentMinute) {
    for (auto& runway : runways) {
        runway.releaseIfExpired(currentMinute);
        if (runway.isAvailable(currentMinute)) {
            return &runway;
        }
    }
    return nullptr;
}

void Scheduler::tick(int currentMinute) {
    // Release any runways whose operations have concluded
    for (auto& runway : runways) {
        runway.releaseIfExpired(currentMinute);
    }

    // Allocate available runways to highest priority flights
    while (!pendingQueue.empty()) {
        Runway* availableRunway = findOptimalRunway(currentMinute);
        if (!availableRunway) {
            break; // All runways busy for this minute
        }

        Aircraft topFlight = pendingQueue.top();
        pendingQueue.pop();

        availableRunway->assignSlot(currentMinute, separationInterval);

        double score = topFlight.calculateUrgencyScore(currentMinute);
        logs.push_back({currentMinute, topFlight.callSign, availableRunway->name, topFlight.type, score});

          cout << "[T+" <<   setw(2) <<   setfill('0') << currentMinute << "m] "
                  << "Runway " << availableRunway->name << " CLEARED for "
                  << topFlight.callSign << " (" << topFlight.typeToString() << ")"
                  << " | Urgency: " <<   fixed <<   setprecision(1) << score
                  << " | Alert: " << topFlight.emergencyToString() << "\n";
    }
}

const   vector<ScheduleLog>& Scheduler::getHistory() const {
    return logs;
}

size_t Scheduler::getPendingFlightCount() const {
    return pendingQueue.size();
}