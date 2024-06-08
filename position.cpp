#include "position.h"

double Position::metersFromPixels = 1.0;

std::ostream& operator<<(std::ostream& out, const Position& pos) {
    out << "(" << pos.getMetersX() << "m, " << pos.getMetersY() << "m)";
    return out;
}

std::istream& operator>>(std::istream& in, Position& pos) {
    double x, y;
    in >> x >> y;
    pos.setMetersX(x);
    pos.setMetersY(y);
    return in;
}