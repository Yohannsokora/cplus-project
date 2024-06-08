#include <iostream>
#include <cmath>
#include <map>
#include "position.h"
#include "ground.h"
#include "uiDraw.h"

// Constants
const double GRAVITY = 9.8;        // m/s^2
const double SHELL_MASS = 46.7;    // kg
const double SHELL_DIAMETER = 0.15489; // m (diameter)
const double SEA_LEVEL_DENSITY = 1.225; // kg/m^3 at sea level
const double SPEED_OF_SOUND = 343; // m/s at sea level

// Air density function (simple exponential decay model)
double airDensity(double altitude) {
    return SEA_LEVEL_DENSITY * exp(-altitude / 8000.0);
}

// Drag coefficient data (based on Mach number)
std::map<double, double> dragCoefficientData = {
    {0.300, 0.1629},
    {0.500, 0.1659},
    {0.700, 0.2031},
    {0.890, 0.2597},
    {0.920, 0.3010},
    {0.960, 0.3287},
    {0.980, 0.4002},
    {1.000, 0.4258}
};

// Function to interpolate drag coefficient based on speed
double getDragCoefficient(double speed) {
    double mach = speed / SPEED_OF_SOUND;
    auto lower = dragCoefficientData.lower_bound(mach);
    auto upper = dragCoefficientData.upper_bound(mach);

    if (lower == dragCoefficientData.end()) return dragCoefficientData.rbegin()->second;
    if (upper == dragCoefficientData.begin()) return dragCoefficientData.begin()->second;

    // Linear interpolation
    double x0 = lower->first;
    double y0 = lower->second;
    double x1 = upper->first;
    double y1 = upper->second;
    
    return y0 + (y1 - y0) * ((mach - x0) / (x1 - x0));
}

// Function to compute drag force using dynamic values
double computeDragForce(double speed, double altitude) {
    double density = airDensity(altitude);
    double dragCoefficient = getDragCoefficient(speed);
    double area = M_PI * std::pow(SHELL_DIAMETER / 2, 2); // Cross-sectional area
    return 0.5 * dragCoefficient * density * area * std::pow(speed, 2);
}

int main() {
    initRandom(); // Initialize random seed

    double angle;
    std::cout << "What is the angle of the howitzer where 0 is up? ";
    std::cin >> angle;

    double angleRadians = angle * M_PI / 180.0;
    double initialSpeed = 827.0; // m/s
    double timeStep = 0.01; // seconds

    // Initial velocities
    double velocityX = initialSpeed * cos(angleRadians);
    double velocityY = initialSpeed * sin(angleRadians);

    // Position initialization
    Position position(0, 0);
    Ground ground(Position(50000, 3000)); // Assuming a large ground area

    ground.reset(position); // Initialize ground and set howitzer position

    // Simulation variables
    double time = 0;
    double distance = 0;
    double maxHeight = 0;
    bool hitGround = false;

    // Simulation loop
    while (!hitGround) {
        // Update positions
        position.addMetersX(velocityX * timeStep);
        position.addMetersY(velocityY * timeStep);

        // Update velocities
        double speed = sqrt(velocityX * velocityX + velocityY * velocityY);
        double dragForce = computeDragForce(speed, position.getMetersY());
        double dragAcceleration = dragForce / SHELL_MASS;

        velocityX -= (dragAcceleration * (velocityX / speed)) * timeStep;
        velocityY -= (GRAVITY + dragAcceleration * (velocityY / speed)) * timeStep;

        // Check for maximum height
        if (position.getMetersY() > maxHeight) {
            maxHeight = position.getMetersY();
        }

        // Check if projectile has hit the ground
        if (position.getMetersY() <= 0) {
            hitGround = true;
            double prevY = position.getMetersY() + velocityY * timeStep;
            double ratio = prevY / (prevY - position.getMetersY());
            double impactDistance = position.getMetersX() - (velocityX * ratio * timeStep);
            time -= timeStep * (1 - ratio);
            distance = impactDistance;
        }

        // Update time
        time += timeStep;
    }

    std::cout << "Distance: " << distance << "m\n";
    std::cout << "Hang Time: " << time << "s\n";

    return 0;
}