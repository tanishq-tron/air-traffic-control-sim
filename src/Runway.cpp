#include "Runway.hpp"

bool Runway::isAvailable(int currentMinute) const {
    return (status == RunwayStatus::IDLE) && (currentMinute >= availableAtMinute);
}

void Runway::assignSlot(int startMinute, int durationMinutes) {
    status = RunwayStatus::OCCUPIED;
    availableAtMinute = startMinute + durationMinutes;
}

void Runway::releaseIfExpired(int currentMinute) {
    if (status == RunwayStatus::OCCUPIED && currentMinute >= availableAtMinute) {
        status = RunwayStatus::IDLE;
    }
}