/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)

{   // straight up
    angle.setUp();

    // Set horizontal velocity to a random value between -4m/s and -10m/s
    velocity.setDX(-random(4.0, 10.0));

    // Set vertical velocity to a random value between -2m/s and 2m/s
    velocity.setDY(random(-2.0, 2.0));

    // Set horizontal position to 1 pixel from the right of the screen
    pos.setX(posUpperRight.getX() - 1.0);

    // Set vertical position to a random value between 75% and 95% of the height of the screen
    pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));

    // status is playing
    status = PLAYING;

    // fill 'er up with fuel
    fuel = FUEL_MAX;



}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
    // Draw the lander
    gout.drawLander(pos, angle.getRadians());

    // Only fire the engine if we are still flying
   if(isFlying() && fuel > 0.0)
    gout.drawLanderFlames(pos, angle.getRadians()),
    thrust.isMain(), thrust.isClock(), thrust.isCounter();
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{   
    //Accelaration due to gravity
   Acceleration a;

   // add gravity
   a.addDDX(gravity);

   //are we out of gas?
   if (fuel == 0.0){
    return a;
   }

   //Main engines
   if (thrust.isMain())
   {
    double power = (LANDER_THRUST / LANDER_WEIGHT);
    a.addDDX(-sin(angle.getRadians()) * power);
    a.addDDY(cos(angle.getRadians()) * power);
    fuel -= FUEL_MAIN_THRUST;
   }

   // clockwise
   if (thrust.isClock())
   {
    angle.add(0.1);
    fuel -= FUEL_ROTATE;
   }
   

   //counter clockwise
   if (thrust.isCounter())
   {
    angle.add(-0.1);
    fuel -= FUEL_ROTATE;
   }

   if (fuel < 0.0){
    fuel = 0.0;

    return a;
   }
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   // Update the velocity
   velocity.add(acceleration, time);
   pos.add(acceleration, velocity, time);
}
