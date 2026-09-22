#include "Aircraft.hpp"
using namespace std;


double Aircraft::calculateUrgencyScore(int currentMinute) const {
    double score = 0.0;

    // 1. Emergency status dominates scheduling decisions
    switch (emergency) {
        case EmergencyLevel::CRITICAL_FAILURE: score += 10000.0; break;
        case EmergencyLevel::MEDICAL:          score += 5000.0;  break;
        case EmergencyLevel::LOW_FUEL:         score += 3000.0;  break;
        case EmergencyLevel::NONE:             score += 0.0;     break;
    }

    // 2. Exponential penalty for depleting fuel (arrivals only)
    if (type == FlightType::ARRIVAL) {
        if (fuelMinutesRemaining <= 15) {
            score += 4000.0 / (fuelMinutesRemaining + 1);
        } else if (fuelMinutesRemaining <= 45) {
            score += 1500.0 / (fuelMinutesRemaining + 1);
        } else {
            score += 300.0 / (fuelMinutesRemaining + 1);
        }
    }

    // 3. Delay penalty (increases weight for delayed flights)
    int delay = currentMinute - scheduledMinute;
    if (delay > 0) {
        score += delay * 5.0;
    }

    return score;
}

  string_view Aircraft::typeToString() const {
    return (type == FlightType::ARRIVAL) ? "ARRIVAL" : "DEPARTURE";
}

  string_view Aircraft::emergencyToString() const {
    switch (emergency) {
        case EmergencyLevel::CRITICAL_FAILURE: return "CRITICAL_FAILURE";
        case EmergencyLevel::MEDICAL:          return "MEDICAL";
        case EmergencyLevel::LOW_FUEL:         return "LOW_FUEL";
        case EmergencyLevel::NONE:             return "NONE";
    }
    return "UNKNOWN";
}