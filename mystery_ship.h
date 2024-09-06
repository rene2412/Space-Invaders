#pragma once
#include "raylib.h"
#include <vector>
#include <thread>
#include <iostream>

class MysteryShip {
private:
	Texture2D image;
	Rectangle ship;
	float width = 60;
	float height = 50;
	Vector2 position;
	float movement_speed = 1.25;
	float last_fly_by = 0;
	bool running;
public:
	MysteryShip() : running(true) {
 	      	image = LoadTexture("images/Mystery_Ship.png");
		position.x = 780;
		position.y = 60;
		ship = { position.x, position.y, width, height };
	}

	~MysteryShip() {
		running = false;
		UnloadTexture(image);
	}
	
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	Rectangle GetMysteryShip() { return ship; }
	Vector2 GetMysteryPosition() { return position; } 
	
	void SetMysteryPosition(Vector2 p) { position = p; }	
	
	void Move() { 
	//	std::cout << "(" << position.x << ", " << position.y << ")\n";
		//mystery ship should across the map once every 7 seconds
		if (GetTime() - last_fly_by >= 7) { 
			if (position.x + width >= 0) {
				position.x -= movement_speed;
				ship.x = position.x;
				ship.y = position.y;
		 } else {
		//when the ship reaches the left wall and is fully sumberged, reset its position and timer for the next fly by
			last_fly_by = GetTime();
			position.x = 780;
			ship.x = position.x;
			ship.y = position.y;
			}	
		}
	}
	
	void Run() {
		while (running) {
		Move();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	}
	
	void Draw() {
		float scaleX = width / image.width;
		float scaleY = height / image.height;
		DrawTextureEx(image, position, 0.0f, scaleX, WHITE);				
	}

	void Stop() { running = false; }
	
	void Reset() {
        // Reset position, timer, and any other relevant attributes
        	position.x = 780;
        	position.y = 60;
        	last_fly_by = GetTime();  // Reset the timer
        	ship.x = position.x;
        	ship.y = position.y;
    }


};
