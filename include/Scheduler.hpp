#pragma once

#include <vector>
#include <queue>
#include <memory>
#include "Aircraft.hpp"
#include "Runway.hpp"

struct ScheduleLog {
    int executionMinute;
    std::string callSign;
    std::string runwayName;
    FlightType flightType;
    double urgencyScore;
};

class Scheduler {
public:
    Scheduler(int separationIntervalMinutes = 3);

    void addRunway(Runway runway);
    void submitFlight(const Aircraft& aircraft);

    // Advances simulation clock by one discrete minute
    void tick(int currentMinute);

    [[nodiscard]] const std::vector<ScheduleLog>& getHistory() const;
    [[nodiscard]] size_t getPendingFlightCount() const;

private:
    int separationInterval;
    std::vector<Runway> runways;
    std::priority_queue<Aircraft, std::vector<Aircraft>, AircraftPriorityComparator> pendingQueue;
    std::vector<ScheduleLog> logs;

    Runway* findOptimalRunway(int currentMinute);
};