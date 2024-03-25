/*  Base class
    float x, y are coords
    k is a constant of increment
*/
#pragma once
#include "cstdlib" //rand() - can get away with not setting the seed
#include "collision.h"

/* Structure for Water Particle */
/* Helps detect Oscillation in the x-axis with */
/* no increments in the y-axis */
struct OscillationDetector
{
    bool bIsLeft = rand() % 2;//initialize to random bool value
    short count = 0;
};
//Once occil_count reaches max, water particle will be set to idle
const int max_Oscilations = 2;


//enum for identifying type of particle in a polymorphic environment
enum DrawType {
    DrawSand,
    DrawWater,
    DrawSolid,
    DrawFreespace   //default when instantiated
};


class Particle
{
public:
    
    //the state that the current particle is either idle or moving
    bool idle;

    //Collision object pointer for all particles
    //Initialized in Driver class
    inline static CollisionBoard* collision;

    //for keeping track of collision counting
    // used in updateParticle()
    short collisionCount;

    //x and y relative to window size
	float x;
	float y;


    //constructors
    Particle(int x, int y);
    virtual ~Particle();

    //Particle Move functions
    void moveBelow();
    void moveLeft();
    void moveRight();
    void moveBelowLeft();
    void moveBelowRight();

    //OVERRIDE THIS
    // returns the particle type to draw for each instance
    virtual DrawType getDrawType();
    

    //OVERRIDE THIS
    /* This contains the rules for each type of particle */
	virtual void updateParticle();
};

/*  Sand Particle   */
class Sand: public Particle
{
public:
    //constants used for incrementing
	static constexpr float speedInFREESPACE = 0.2f;
    static constexpr float speedInWATER = 0.05f;

    //keep track of which pixel color to draw
    //called in driver class
    static const DrawType drawType = DrawSand;

    Sand(int x, int y);

    //This returns the particle type to draw for each instance
    virtual DrawType getDrawType();

    void updateParticle() override;
};

/*  Water Particle   */
class Water: public Particle
{
public:
    //for incrementing
	static constexpr float speedInFREESPACE = 0.2f;

    //keep track of which pixel color to draw
    //called in driver class
    static const DrawType drawType = DrawWater;

    //structure for determining possible oscillation in the x-axis
    // ie left , right , left , right
    OscillationDetector occil_detector;

    Water(int x, int y);

    //This returns the particle type to draw for each instance
    DrawType getDrawType() override;


    void updateParticle() override;
};

/*  Solid Particle   */
class Solid: public Particle
{
public:
    Solid(int x, int y);

    //keep track of which pixel color to draw
    //called in driver class
    static const DrawType drawType = DrawSolid;

    //This returns the particle type to draw for each instance
    DrawType getDrawType() override;
};