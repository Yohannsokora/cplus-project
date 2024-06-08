#include "ground.h"
#include "uiDraw.h"
#include <cassert>

const int WIDTH_HOWITZER = 14;
const double MIN_ALTITUDE = 300.0;
const double MAX_ALTITUDE = 3000.0;
const double MAX_SLOPE = 1.0;
const double LUMPINESS = 0.15;
const double TEXTURE = 3.0;

Ground::Ground(const Position & posUpperRight) :
    posUpperRight(posUpperRight),
    iHowitzer(0),
    iTarget(0),
    ground(nullptr) {
    ground = new double[(int)posUpperRight.getPixelsX()];
}

double Ground::getElevationMeters(const Position& pos) const {
    Position posImpact(pos);

    if (pos.getPixelsX() >= 0.0 && pos.getPixelsX() < (int)posUpperRight.getPixelsX())
        posImpact.setPixelsY(ground[(int)pos.getPixelsX()]);
    else
        posImpact.setPixelsY(0.0);

    return posImpact.getMetersY();
}

Position Ground::getTarget() const {
    assert(iTarget >= 0 && iTarget < posUpperRight.getPixelsX());
    Position posTarget;
    posTarget.setPixelsX(iTarget);
    posTarget.setPixelsY(ground[iTarget]);
    return posTarget;
}

void Ground::reset(Position & posHowitzer) {
    int width = (int)posUpperRight.getPixelsX();
    assert(width > 0);

    iHowitzer = (int)(posHowitzer.getPixelsX());
    if (iHowitzer > width / 2)
        iTarget = random((int)(width * 0.05), (int)(width * 0.45));
    else
        iTarget = random((int)(width * 0.55), (int)(width * 0.95));

    Position posMinimum(0.0, MIN_ALTITUDE);
    Position posMaximum(posUpperRight.getMetersX(), MAX_ALTITUDE);

    ground[0] = posMinimum.getPixelsY();
    double dy = MAX_SLOPE / 2.0;
    for (int i = 1; i < width; i++) {
        if (i > iHowitzer - WIDTH_HOWITZER / 2 && i < iHowitzer + WIDTH_HOWITZER / 2) {
            ground[i] = ground[i - 1];
        } else {
            double percent = (ground[i - 1] - posMinimum.getPixelsY()) /
                             (posMaximum.getPixelsY() - posMinimum.getPixelsY());

            dy += (1.0 - percent) * random(0.0, LUMPINESS) +
                  (percent) * random(-LUMPINESS, 0.0);

            if (dy > MAX_SLOPE)
                dy = MAX_SLOPE;
            if (dy < -MAX_SLOPE)
                dy = -MAX_SLOPE;

            ground[i] = ground[i - 1] + dy + random(-TEXTURE, TEXTURE);
            assert(ground[i] >= 0.0 && ground[i] <= posUpperRight.getPixelsY());
        }
    }

    posHowitzer.setPixelsY(ground[iHowitzer]);
}
