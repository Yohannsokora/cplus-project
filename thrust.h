/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

/*****************************************************
 * THRUST
 * Represents activation of thrusters
 *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per frame
   double rotation() const
   {
      return(clockwise ? 0.1 : 0.0) +
      (counterClockwise ? -0.1 : 0.0);
   }

   // Get main engine thrust in m/s^2
   double mainEngineThrust() const
   {
      // Thrust (N) = 45000 N, Mass (kg) = 15103 kg
      return 45000.0 / 15103.0;
   }

   // Reflect what is firing
   bool isMain() const { return mainEngine; }
   bool isClock() const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   // Set the thrusters based on user input
   void set(const Interface * pUI)
   {
      mainEngine = pUI->isDown();
      clockwise = pUI->isRight();
      counterClockwise = pUI->isLeft();
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
