#pragma once
#include <iostream>

class Position {
public:
    Position() : x(0.0), y(0.0) {}
    Position(double x, double y) : x(x), y(y) {}

    // Getters and setters
    double getMetersX() const { return x; }
    double getMetersY() const { return y; }
    double getPixelsX() const { return x / metersFromPixels; }
    double getPixelsY() const { return y / metersFromPixels; }
    void setMetersX(double xVal) { x = xVal; }
    void setMetersY(double yVal) { y = yVal; }
    void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
    void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }
    void addMetersX(double dx) { x += dx; }
    void addMetersY(double dy) { y += dy; }

    // Deal with the ratio of meters to pixels
    void setZoom(double metersFromPixels) {
        this->metersFromPixels = metersFromPixels;
    }
    double getZoom() const { return metersFromPixels; }

    friend std::ostream& operator<<(std::ostream& out, const Position& pos);
    friend std::istream& operator>>(std::istream& in, Position& pos);

private:
    double x;
    double y;
    static double metersFromPixels;
};

std::ostream& operator<<(std::ostream& out, const Position& pos);
std::istream& operator>>(std::istream& in, Position& pos);
