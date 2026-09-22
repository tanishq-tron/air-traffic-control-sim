#pragma once

#include <string>
#include <string_view>

enum class FlightType {
    ARRIVAL,
    DEPARTURE
};

enum class EmergencyLevel {
    NONE = 0,
    LOW_FUEL = 1,
    MEDICAL = 2,
    CRITICAL_FAILURE = 3
};

struct Aircraft {
    std::string callSign;
    FlightType type;
    int fuelMinutesRemaining;
    EmergencyLevel emergency;
    int scheduledMinute;

    [[nodiscard]] double calculateUrgencyScore(int currentMinute) const;
    [[nodiscard]] std::string_view typeToString() const;
    [[nodiscard]] std::string_view emergencyToString() const;
};

// Custom comparator for std::priority_queue (Max-Heap based on urgency)
struct AircraftPriorityComparator {
    int currentMinute{0};

    explicit AircraftPriorityComparator(int minute = 0) : currentMinute(minute) {}

    bool operator()(const Aircraft& lhs, const Aircraft& rhs) const {
        return lhs.calculateUrgencyScore(currentMinute) < rhs.calculateUrgencyScore(currentMinute);
    }
};