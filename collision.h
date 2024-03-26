/*  this is the collision mechanism that the sandDemo uses
    Utilizes a 2D vector size: (screenWidth, screenHeight) inorder to track
    all particles, and keep particles seperated, thus mimicking
    a collision system
*/
/* PixelTypes to be stored into 2D vector */
#pragma once
#include <vector>

enum PixelType
{
    FREESPACE,  //0
    SOLID,      //1
    SAND,       //2
    WATER       //3
};

class CollisionBoard
{
protected:
    //track all particles
    std::vector<std::vector<PixelType>> board;

public:
    //Resolution of the Window
    int width, height;

    //board height
    int board_height;

    //Constructors
    CollisionBoard(int width, int height);

    //Return the Particle ( if any ) in the board at  (x , y)
    PixelType CheckBelow        (int x, int y);
    PixelType CheckBelowLeft    (int x, int y);
    PixelType CheckBelowRight   (int x, int y);
    PixelType CheckLeft         (int x, int y);
    PixelType CheckRight        (int x, int y);

    //Set pixelType to the board at (x , y)
    void setPixelType(int x, int y, PixelType type);

    /*  Invoked everytime collision-board is cleared or instantiated  */
    //Set the Floor to solid
    void setFlooring();
    //Set the Walls to solid
    void setWalls();

    //Clear the CollisionBoard vector
    void clear();

};