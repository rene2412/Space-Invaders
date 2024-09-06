#pragma once 
#include <raylib.h>
#include "laser.h"
#include "mystery_ship.h"
#include "user_info.h"
#include <vector>

class SpaceShip {
private:
    Texture2D image;
    Rectangle spaceship;
    Vector2 position;
    std::vector<Laser> lasers;
    float lastFireTime;
    int spaceship_laser_speed = 7;
    const int movement = 7;
public:
    // Constructor
    SpaceShip() {
        image = LoadTexture("images/spaceship.png");
        position.x = (GetScreenWidth() - image.width) / 2;
        position.y = GetScreenHeight() - image.height;
	lastFireTime = 0.0;    
	spaceship = { position.x, position.y, (float)image.width, (float)image.height };
	}

    // Destructor
    ~SpaceShip() {
        UnloadTexture(image); 
   }
    // Getter for the lasers vector
    std::vector<Laser>& Get_Lasers()  { return lasers; }
    Rectangle GetSpaceShip() { return spaceship; }
    float GetWidth() const { return (float)image.width; }
    float GetHeight() const { return (float)image.height; }

    void SetSpaceShipPosition(Vector2 p) {
		 position = p;
		 spaceship.x = position.x;
		 spaceship.y = position.y;
 } 
   // Member function to draw the spaceship
    void Draw() {
        DrawTextureV(image, position, GOLD);
    }

    void MoveLeft() {
	position.x -= movement;		
	if (position.x < 0 ) {
		position.x = 0;
	   } 
	spaceship.x = position.x;
	spaceship.y = position.y;
     }
    
    void MoveRight() {
	position.x += movement;
	if (position.x > GetScreenWidth() - image.width) {
		position.x = GetScreenWidth() - image.width;
 	    }  
	spaceship.x = position.x;
	spaceship.y = position.y;
       }

    void FireLaser() {
	if (GetTime() - lastFireTime >= 0.35) { 
		lasers.push_back(Laser({position.x + (image.width / 2) - 2, position.y}, spaceship_laser_speed, true));	
		lastFireTime = GetTime();	
	  } 
     }  

};

