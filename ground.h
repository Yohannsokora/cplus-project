#pragma once
#include "position.h"

class Ground {
public:  
    Ground(const Position &posUpperRight);
    Ground() : ground(nullptr), iHowitzer(0), iTarget(0) {}

    void reset(Position & posHowitzer);
    double getElevationMeters(const Position & pos) const;
    Position getTarget() const;

private:
    double * ground;
    int iTarget;
    int iHowitzer;
    Position posUpperRight;
};
