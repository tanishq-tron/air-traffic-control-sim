#pragma once

#include <string>

enum class RunwayStatus {
    IDLE,
    OCCUPIED,
    MAINTENANCE
};

struct Runway {
    int id;
    std::string name;             // e.g., "09L", "27R"
    RunwayStatus status{RunwayStatus::IDLE};
    int availableAtMinute{0};      // Time slot when separation constraint is satisfied

    [[nodiscard]] bool isAvailable(int currentMinute) const;
    void assignSlot(int startMinute, int durationMinutes);
    void releaseIfExpired(int currentMinute);
};