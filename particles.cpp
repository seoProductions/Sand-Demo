/*  Implementation for
    Sand and Water class
*/
#include "particles.h"

/***************** Base Class - Particle Implementation *******************/
Particle::Particle(int x, int y)
{
    this->x = x;
    this->y = y;

    idle = false;    //default
}
Particle::~Particle() { }
DrawType Particle::getDrawType() { return DrawFreespace; }

void inline Particle::updateParticle()
{
    //nada
}


/************************** Sand Implementation **************************/
Sand::Sand(int x, int y) : Particle(x, y) { }

DrawType Sand::getDrawType() { return DrawSand; }


void Sand::updateParticle()
{
    //keep track of collisions
    collisionCount = 0; //reset

    switch (collision->CheckBelow(x,y))
    {
    case FREESPACE:
        y += speedInFREESPACE;//increment
        break;

    case SOLID:
        //Instantly set to Sand
        collision->setPixelType(x,y, SAND);
        break;
    
    case WATER:
        //**Sand CAN move into water**
        //still falling, but at a slower rate
        y += speedInWATER;
        break;

    case SAND:
    {
        //Check the sides of the sand particle below it
        //Simulates sand falling / collapsing

        //Randomly choose Left/ or Right. 1 in 2 chance
        if (rand() % 2)
        {
            //first right, then left
            switch (collision->CheckBelowRight(x,y))
            {
                case FREESPACE:
                    //Space Available, thus particle
                    //can move there - update coords
                    moveBelowRight();
                    break;
                case WATER:
                    //**Sand CAN move into water**
                    moveBelowRight();
                    break;
                default:
                    ++collisionCount;
                
            }
            
            //if particle's collided, check other side
            if (collisionCount != 0)
            switch (collision->CheckBelowLeft(x,y))
            {
                case FREESPACE:
                    //Space Available, thus particle
                    //can move there - update coords
                    moveBelowLeft();
                    break;
                case WATER:
                    //**Sand CAN move into water**
                    moveBelowLeft();
                    break;
                default:
                    ++collisionCount;
                
            }
            
        }
        else
        {
            //first left, then right
            switch (collision->CheckBelowLeft(x,y))
            {
                case FREESPACE:
                    //Space Available, thus particle
                    //can move there - update coords
                    moveBelowLeft();
                    break;
                case WATER:
                    //**Sand CAN move into water**
                    moveBelowLeft();
                    break;
                default:
                    ++collisionCount;
                
            }
            
            //if particle's collided, check other side
            if (collisionCount != 0)
            switch (collision->CheckBelowRight(x,y))
            {
                case FREESPACE:
                    //Space Available, thus particle
                    //can move there - update coords
                    moveBelowRight();
                    break;
                case WATER:
                    //**Sand CAN move into water**
                    moveBelowRight();
                    break;
                default:
                    ++collisionCount;
                
            }
        }

        //If particle has nowhere to go
        //Set particle's (x,y) coords to sand on the collision board
        //Stationary sand particle
        if (collisionCount > 1) {
            collision->setPixelType(x,y,SAND);
            idle = true; //particle is now stationary
        }

        //End - Sand colliding with Sand
        break;
    }

    default:
        break;
    }
    
}

/************************** Water Implementation **************************/
Water::Water(int x, int y) : Particle(x, y) { } //Pass in appropriate parameters
DrawType Water::getDrawType() { return DrawWater; }


void Water::updateParticle()
{
    //keep track of collisions
    collisionCount = 0; //reset

    /*  FIRST - Check IF oscillation count exceeded maximum oscillations   */
    if (occil_detector.count >= max_Oscilations)
    {
        //set to idle and update collision board
        collision->setPixelType(x,y,WATER);
        idle = true; //particle is now stationary
        return; //Quit updating particle
    }

    switch (collision->CheckBelow(x,y))
    {
        //still falling so increment y by a constant
        case FREESPACE:
        {
            y += speedInFREESPACE;//increment

            occil_detector.count = 0; //reset counter
            break;
        }
        //default is when particle collides when falling
        default:
        {
            switch (occil_detector.bIsLeft)
            {
            //==========================  LEFT =======================
            case true: {
                //Check Left side inorder to move there
                switch (collision->CheckLeft(x,y))
                {
                    case FREESPACE:
                    {

                        //Space Available, check for Corners
                        switch (collision->CheckBelowLeft(x,y))
                        {
                            case FREESPACE:
                            {
                                //space available in the corner
                                //move there
                                moveBelowLeft();
                                break;
                            }
                            //else move left (as intended)
                            default: 
                            {
                                moveLeft();
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        ++collisionCount;
                        break;
                    }
                }

                //if particle's collided, check other side
                if (collisionCount != 0) {
                switch (collision->CheckRight(x,y))
                {
                    case FREESPACE:
                    {
                        //PARTICLE WILL CHANGE DIRECTION
                        //Update direction in the oscillationDetector
                        //increment , and switch direction to the RIGHT
                        occil_detector.bIsLeft = false;
                        ++occil_detector.count;

                        //* Particle will move if compilations have not been exceeded
                        if (occil_detector.count >= max_Oscilations)

                            //Space Available, check for Corners
                            break;
                        switch (collision->CheckBelowRight(x, y)) {
                            case FREESPACE: {
                                //space available in the corner
                                //move there
                                moveBelowRight();
                                break;
                            }
                                //else move left (as intended)
                            default: {
                                moveRight();
                                break;
                            }
                        }

                        break;
                    }
                    default:
                    {
                        ++collisionCount;
                        break;
                    }
                }}
                break;
            }
            
            //======================  END LEFT ========================


            //==========================  RIGHT =======================
            case false: {
                //Check Left side inorder to move there
                switch (collision->CheckRight(x,y))
                {
                    case FREESPACE:
                    {

                        //Space Available, check for Corners
                        switch (collision->CheckBelowRight(x,y))
                        {
                            case FREESPACE:
                            {
                                //space available in the corner
                                //move there
                                moveBelowRight();
                                break;
                            }
                            //else move left (as intended)
                            default: 
                            {
                                moveRight();
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        ++collisionCount;
                        break;
                    }
                }

                //if particle's collided, check other side
                if (collisionCount != 0) {
                switch (collision->CheckLeft(x,y))
                {
                    case FREESPACE:
                    {

                        //PARTICLE WILL CHANGE DIRECTION
                        //Update direction in the oscillationDetector
                        //increment , and switch direction to the LEFT
                        occil_detector.bIsLeft = true;
                        ++occil_detector.count;

                        //* Particle will move if compilations have not been exceeded
                        if (occil_detector.count >= max_Oscilations)

                            //Space Available, check for Corners
                            break;
                        switch (collision->CheckBelowLeft(x, y)) {
                            case FREESPACE: {
                                //space available in the corner
                                //move there
                                moveBelowLeft();
                                break;
                            }
                                //else move left (as intended)
                            default: {
                                moveLeft();
                                break;
                            }
                        }

                        break;
                    }
                    default:
                    {
                        ++collisionCount;
                        break;
                    }
                }}
                break;

            }
            //======================  END RIGHT ========================

            }
            //If particle has nowhere to go
            //Set particle's (x,y) coords to water on the collision board
            //Stationary Water particle
            if (collisionCount > 1)
            {
                collision->setPixelType(x,y,WATER);
                idle = true; //particle is now stationary
            }
        }
    }
}


/************************** Solid Implementation **************************/
Solid::Solid(int x, int y):  Particle(x, y) //Pass in appropriate parameters
{
    //Set particle's (x,y) coords to solid
    collision->setPixelType(x,y,SOLID);
    idle = true; //solid particle is always stationary
}
DrawType Solid::getDrawType() { return DrawSolid; }


/*  Particle Move Functions  */
/*  Always check if inbounds */
/*    With inline Request    */

inline void Particle::moveBelow()
{ 
    switch (y < collision->height - 1)
    {
        case true:
        {
            ++y;
            break;
        }
        case false:
        {
            ++collisionCount;
            break;
        }
    }
}
inline void Particle::moveLeft() 
{ 
    switch (x > 0)
    {
        case true:
        {
            --x;
            break;
        }
        case false:
        {
            ++collisionCount;
            break;
        }
    }
}
inline void Particle::moveRight()
{
    switch (x < collision->width - 1)
    {
        case true:
        {
            ++x;
            break;
        }
        case false:
        {
            ++collisionCount;
            break;
        }
    }
}
inline void Particle::moveBelowLeft()
{
    switch (y < collision->height - 1 && x > 0)
    {
        case true:
        {
            --x;
            ++y;
            break;
        }
        case false:
        {
            ++collisionCount;
            break;
        }
    }
}
inline void Particle::moveBelowRight()
{
    switch (y < collision->height - 1 && x < collision->width - 1)
    {
        case true:
        {
            ++x;
            ++y;
            break;
        }
        case false:
        {
            ++collisionCount;
            break;
        }
    }
}