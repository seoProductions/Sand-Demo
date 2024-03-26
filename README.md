
# Welcome to my Sand Demo, take a look!!

A simple project that simulates sand and water particles acting on a 2D world. This project utilizes the concept of a cellular automata, combined with Object Oriented and Function programing.


# Features
#### Sand
![sand_demonstration](https://github.com/seoProductions/Sand-Demo/assets/111206081/c46b3575-7001-45c1-91c8-3eb74aef66df)


#### Water
![water_demonstration](https://github.com/seoProductions/Sand-Demo/assets/111206081/f9902f85-b0b3-4a31-a1d5-f9c2f65e2d69)


#### Solid (WALL)
![water_pour](https://github.com/seoProductions/Sand-Demo/assets/111206081/5dedddaf-0efa-4da3-af5d-78d6465fee62)


#### Here are some more demonstrations: 
![stream_demonstration](https://github.com/seoProductions/Sand-Demo/assets/111206081/b16c889f-c8e7-4672-9f94-90b2b38066bf)


![Cube Demonstration](https://github.com/seoProductions/Sand-Demo/assets/111206081/494bbe5f-07b4-42a3-a54a-9f9a033c2324)


#### This is a messy one!
![messy_one](https://github.com/seoProductions/Sand-Demo/assets/111206081/ed71eea2-67c8-49b4-84a2-0453b6407f99)


## Lessons Learned

While building this project, I both learned and tested many skills including
- Project Design
- Memory manegment (Dynamic Memory)
- How to Debug effectivley. Especially SEG FAULTS
- Naming Conventions
- Polymorphism and Inheritance
- Shell Scripting on linux
- How compilation and linking works in c++
-  Version controll using git 
Here is a birds eye view of the project and its structure. Included is a UML Diagram 

<PHOTO>

# Gist of the program

The program first launches into the main function where I have created a class called Engine.

```c++
class Engine : public olc::PixelGameEngine
```



This class is derived directly from the PixelGameEngine's Base class. The base class handles nessesary functionality such as 
 - Window creation
 - Drawing
 - Keyboard and Mouse Inputs

 Looking into the Engine Class, I have a collection of Pointers of type "Particle" (More info on that later). I have these pointers held into std::vector simply due to simplicity and efficiency.

```c++
std::vector<std::shared_ptr<Particle>> particles;
```

 During the game loop, the Engine checks for a Left click from the user. If sucessfull, new "Particle" pointers are dynamically allocated into the std::vector container.

 ```c++
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
```

Each Particle is iterated over as shown here:

```c++
for (auto particle: particles)
{
	// check bounds and idle status
	if (particle->y < ScreenHeight() - 1 && !particle->idle)
        particle->updateParticle(); //update

	
	//draw a pixel depending on the particle's type
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
 ```
the virtual updateParticle() method is invoked, and the Engine chooses a pixel color and pixel position to draw onto the screen. 

## Particle
This is the meat and Potatoes. The Particle class is the parent class for all particle types.

```c++
class Particle
```
this class contains
- x and y position
- idle status
- generic "move" methods
- virtual methods

Base classes are

```c++
class Sand : public Particle
class Water: public Particle
class Solid: public Particle

```
They each contain 
- specific update function 
- specific DrawType

### Special case:
Each water particle has a structure called "OscilationDetector". It simply aids in determining when to put a water particle into idle

```c++
struct OscillationDetector

```
### Particle Rules and behavior
- Solid particles never move and are always idle
- Sand particles will try to move below, then below to the (left/right)
- Water particles do the same as sand, exept they also try to move directly (left/right)

The implementation for the rules was the most tedious part of my project, including many long and painfull debugging sessions, and crazy unexpected bugs. At the end, I got a working prototype! Far from perfect, but much more better than what I started off with.

## Collision Detection using "CollisionBoard"
Each particle has a static member of a CollisionBoard. This variable is set in the Engine class, and is used by all particles when checking their movements. Methods include:  
```c++
PixelType CheckBelow        (int x, int y);
PixelType CheckBelowLeft    (int x, int y);
PixelType CheckBelowRight   (int x, int y);
PixelType CheckLeft         (int x, int y);
PixelType CheckRight        (int x, int y);

void setPixelType(int x, int y, PixelType type);
```

The whole std::vector or "board" is initialized to FreeSpace inside the constructor.+

## Time
I have created a Time class with purley static variables and a single function
```c++
static float& getDeltaTime();
```
Simple, yet effective.



## Enumerations

Looking at the UML, you can see I have created three Enumerations scattered around my program. These are helpfull features that I used to develop this program
 - The "KeyDown" enum is used to track which keyboard buttons have been recently pressed
 - The "DrawType" enum is used to identify particle types present in the std::vector of Particles. I figured this was the simplest way to impliment this, wanting to avoid dynamic casting and other perplexing methods capable of throwing exeptions...
 - "PixelType" enum is primarily used in the "CollisionBoard" class. It servers as the collection type used in a 2D std::vector called "board". With this, the CollisionBoard class has a sence of - what particles are in the 2D worlds and the position in which it is at. This is crucial for simulating real-time collision

```c++
std::vector<std::vector<PixelType>> board;
 ```


## Running the program

To run the program, run the following command

```bash
chmod +x run.sh
./run.sh
```

Or simply compile with your compliler of choice. I am using g++ here

```bash
#!/bin/bash
g++ -o driver driver.cpp \
              collision.h \
              collision.cpp \
              particles.h   \
              particles.cpp \
              -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
./driver
```


## Screenshots

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)


## Q&A


#### What made you choose c++ for this project?

I had been using c++ for close to a year now - at the time of making this project (2023). I had grown fairly comfortorable with the language, but not to the point where I could develop larger scale projects. I took on this project our of pure curiosity and initiative. As a result, I ended up learning  much more than I anticipated. And lets not forget the great performance c++ has!

#### What made you choose olc's PixelGameEngine?

The developer of the game engine is a favorite youtuber of mine, and I take great inspiration from him. I picked up the game engine during Highschool - a time when I was exploring many fields in computing. This included: Reverse-Engineering, 3D graphics, Game Developement, and much more. I was exploring at the time, and I just so happened to be familiar with the PixelGameEngine I used in my Sand Demo.

#### I see your std::vector uses shared_ptr's , why not unique_ptr's?


I am using shared pointers because the iterator generated from the code block above - incriments the total instances of this pointer. A unique ptr woudnt allow me to generate an iterator of Particles, and I simply wanted to keep things simple

Answer 2


## Related

Here are some related projects:

[Physics-Simulation in C++](https://github.com/seoProductions/Sandy---Physics-Simulation)


## Authors

- [@seoProductions](https://github.com/seoProductions)


## License

[MIT](https://choosealicense.com/licenses/mit/)

