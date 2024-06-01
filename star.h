/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once

#include "uiDraw.h"  // for ogstream and drawStar
#include "position.h"  // for Position class
#include <cstdlib>  // for rand
#include <ctime>    // for time

class Star
{
public:
    
    Star(): phase(0) {}
    // Set the location of the star field a random phase
    void reset(double width, double height)
    {
        pos.setX(random(0.0, width));
        pos.setY(random(0.0, height));
        phase = random(0, 255);
    }

    // Draw thes star and increment the twinkle number
    void draw(ogstream & gout)
    {
        gout.drawStar(pos, phase++);
    }

private:
    Position pos; //The location of the star
    unsigned char phase; // The phase of the twinkle

};


