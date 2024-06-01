/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <iostream>      // for debugging
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight)
      : lander(posUpperRight), ground(posUpperRight), gravity(-1.625), timeStep(0.1)
   {
      
   }

   void update(const Interface* pUI)
   {
      if (!isRunning())
         return;

      handleInput(pUI);

      // Apply gravity to the lander
      const double gravity = -1.625;

      // Handle user input and get acceleration
      Acceleration acceleration = lander.input(thrust, gravity);

      // Update the lander's position every 0.1 seconds if it hasn't landed anywhere
      if (!ground.onPlatform(lander.getPosition(), lander.getWidth()) && !ground.hitGround(lander.getPosition(), lander.getWidth()))
      {
         lander.coast(acceleration, 0.1);
      }

      // Check if conditions for landing or crashing are met
      if (ground.hitGround(lander.getPosition(), lander.getWidth()) || 
          (ground.onPlatform(lander.getPosition(), lander.getWidth()) && lander.getMaxSpeed() < lander.getSpeed()))
      {
         lander.crash(); // Fail, crash!!!
      }
      else if (ground.onPlatform(lander.getPosition(), lander.getWidth()) && lander.getMaxSpeed() >= lander.getSpeed())
      {
         lander.land(); // Success, landed!!!!
      }
   }

   void draw(ogstream& gout) const
   {
      // Draw the ground
      ground.draw(gout);

      // Draw the lander
      lander.draw(thrust, gout);
   }

   void handleInput(const Interface* pUI)
   {
      // Set the thrusters based on user input
      thrust.set(pUI);
   }

   bool isRunning() const
   {
      return lander.isFlying();
   }

private:
   Ground ground;
   Lander lander;
   Thrust thrust;
   double gravity;
   double timeStep;
};


/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // Cast the void pointer into a Simulator object
   Simulator * pSimulator = (Simulator *)p;

   ogstream gout;

   // Update the simulation state
   pSimulator->update(pUI);

   // Draw the current state
   pSimulator->draw(gout);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
