/*Implementation for the Collision Class */
//track all particles'
#include "collision.h"

//Constructors
CollisionBoard::CollisionBoard(int width, int height)
{
    //set member variables
    this->width = width;
    this->height = height;
    this->board_height = height - 17; //CAN BE CHANGED
    //not sure why 17 works, *TODO* look into it

    //resize 
    //initialize whole board to freespace
    board.resize(height, std::vector<PixelType>(width, FREESPACE));
    //and set floor
    setFlooring();
    setWalls();
}

//Return the Particle ( if any ) in the board starting at (x , y)
PixelType CollisionBoard::CheckBelow(int x, int y)
{
    //make sure in bounds
    if (y + 1 >= board.size()) return SOLID; //default

    return board[y + 1][x];
}
PixelType CollisionBoard::CheckBelowLeft(int x, int y)
{
    //make sure in bounds
    if (y + 1 >= board.size() || x - 1 < 0) return SOLID; //default

    return board[y + 1][x - 1];
}
PixelType CollisionBoard::CheckBelowRight(int x, int y)
{
    //make sure in bounds
    if (y + 1 >= board.size() || x + 1 >= board[0].size()) return SOLID; //default

    return board[y + 1][x + 1];
}
PixelType CollisionBoard::CheckLeft(int x, int y)
{
    //make sure in bounds
    if (x - 1 < 0) return SOLID; //default

    return board[y][x - 1];
}
PixelType CollisionBoard::CheckRight(int x, int y)
{
    //make sure in bounds
    if (x + 1 >= board[0].size()) return SOLID; //default

    return board[y][x + 1];
}

//Set pixelType to the board at (x , y)
void CollisionBoard::setPixelType(int x, int y, PixelType type)
{
    board[y][x] = type;
}

//Set the Floor to solid
//Invoked everytime collision-board is cleared or instantiated
inline void CollisionBoard::setFlooring()
{
    int x = 0;
    for (; x < width; x++) //last row
    {
        board[board_height][x] = SOLID;
    }
}

//Set the Floor to solid
//Invoked everytime collision-board is cleared or instantiated
inline void CollisionBoard::setWalls()
{
    //left wall
    int y = 0;
    for (; y < board_height; y++)
    {
        board[0][y] = SOLID;
    }
    //right wall
    y = 0;
    for (; y < board_height; y++)
    {
        board[width - 1][y] = SOLID;
    }
}

//Clear CollisionBoard vector
void CollisionBoard::clear() 
{ 
    //fill 2D board vector with FREESPACE
    board.resize(height, std::vector<PixelType>(width, FREESPACE));

    //reset floor and walls as solid
    setFlooring();
    setWalls();

}