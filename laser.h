#pragma once
#include "raylib.h"
#include <iostream>

class Laser {
private:
	Vector2 position;
	Rectangle SpaceShipLaser;
	Rectangle AlienLaser;
	int speed = 0;
	bool is_active = false;
public:
	Laser() {}
      
        Laser(Vector2 p, int s, bool a) : position(p),  speed(s), is_active(a) {
		SpaceShipLaser = { position.x, position.y, 4, 15 };
		AlienLaser = { position.x, position.y, 4, 15 };
	}
	
        bool Is_Active() const { return is_active; }	
	
	Rectangle GetSpaceShipLaser() const { return SpaceShipLaser; }
	Rectangle GetAlienLaser() const { return AlienLaser; }
	
	void Update_SpaceShip_Laser() {
		//wherever the laser is at the y axis, increase its speed by the variable speed (which is 7)
		position.y -= speed;
		SpaceShipLaser.x = position.x;
		SpaceShipLaser.y = position.y;
		if (is_active) {
			if (position.y > GetScreenHeight() or position.y < 0) {
				is_active = false;
			}
		}
	}

	void Update_Alien_Laser() {
		position.y += speed;
		AlienLaser.x = position.x;
		AlienLaser.y = position.y;
		//std::cout << "( " << AlienLaser.x << ", " << AlienLaser.y << ")\n";
		if (is_active) { 
			if (position.y > GetScreenHeight()) {
				//std::cout << "Alien Laser Deactivated\n";
				is_active = false;
			}
		}
	}
	
	void Deactivate() {
		is_active = false;
	}
		
	void Draw() {
		//Make a rectangle of width 4 and height 15, and make it yellow
	   if (is_active) { 
		DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
	   }
       }	



};
