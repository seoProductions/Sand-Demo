/*	Driver program using olc::PixelGameEngine
	TODO
*/

#define OLC_PGE_APPLICATION
#include "time.h"
#include "collision.h"
#include "particles.h"
#include "PixelGameEngine/olcPixelGameEngine.h"

//track key presses
enum KeyDown { SandDown, WaterDown, SolidDown };

class Engine : public olc::PixelGameEngine
{
	//vector of particles, holds all instances on screen
	//shared_ptr inorder to use Polymorphism
	std::vector<std::shared_ptr<Particle>> particles;

	//Sand
	olc::Pixel sandColor;
	olc::Pixel waterColor;
	olc::Pixel solidColor;

	//Tracking which particle to instantiate
	//with key pressed
	uint CurrentKeyDown;

public:
	Engine(){ sAppName = "SandGame"; }

public:
	bool OnUserCreate() override
	{
		//seed
		srand(time(0));

		//set colors
		sandColor.r = 255;
		sandColor.g = 230;
		sandColor.b	= 140;
		
		waterColor = olc::BLUE;
		solidColor = olc::DARK_GREY;



		//Set Default KeyState
		CurrentKeyDown = SandDown;

		//instantiating a global CollisionBoard object
		//passed into Particle Class
		Particle::collision = new CollisionBoard(
								ScreenHeight(), ScreenWidth());

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		//If 'C' Pressed, Clear all particles on screen
		if (GetKey(olc::C).bPressed)
		{
			Particle::collision->clear();
			particles.clear();
		}


		//Update settings - Which particle to instantiate
		if (GetKey(olc::K1).bPressed) CurrentKeyDown = SandDown;
		if (GetKey(olc::K2).bPressed) CurrentKeyDown = WaterDown;
		if (GetKey(olc::K3).bPressed) CurrentKeyDown = SolidDown;

		//When mouse held , instantiate particles
		if (GetMouse(0).bHeld)
		{
			switch (CurrentKeyDown)
			{
				case SandDown:
					particles.push_back(
						std::make_shared<Sand>(GetMouseX(), GetMouseY()));
						break;
				case WaterDown:
					particles.push_back(
						std::make_shared<Water>(GetMouseX(), GetMouseY()));
						break;
				case SolidDown:
					particles.push_back(
						std::make_shared<Solid>(GetMouseX(), GetMouseY()));
						break;
			}
		}

		//Functionality for each particle in vector
		for (auto particle: particles)
		{
			// check to see if particle has not hit the floor
			// and not stationary
			switch (particle->y < ScreenHeight() - 1 && !particle->idle)
			{
				case true:
					particle->updateParticle(); //update
			}
			
			//draw particle depending on the type of particle 
			//***Pixel color changes***
			switch (particle->getDrawType())
			{
			case DrawSand:
				Draw(particle->x, particle->y, sandColor);
				break;
			case DrawWater:
				Draw(particle->x, particle->y, waterColor);
				break;
			case DrawSolid:
				Draw(particle->x, particle->y, solidColor);
				break;
			}
			
		}
		
		
		return true; //for olc::game engine
	}
};


int main()
{
	Engine game;
	if (game.Construct(256, 240, 10, 10))   /* FEEL FREE TO MESS AROUND WITH DIMENSIONS! */
		game.Start();

	return 0;
}
