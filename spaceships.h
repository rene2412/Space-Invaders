#pragma once 
#include <raylib.h>

class SpaceShip {
private:
    Texture2D image;
    Vector2 position;
    const int movement = 7;
public:
    // Constructor
    SpaceShip() {
        image = LoadTexture("images/spaceship.png");
        position.x = (GetScreenWidth() - image.width) / 2;
        position.y = GetScreenHeight() - image.height;
    }

    // Destructor
    ~SpaceShip() {
        UnloadTexture(image);
    }

    // Member function to draw the spaceship
    void Draw() {
        DrawTextureV(image, position, WHITE);
    }

    void MoveLeft() {
	position.x -= movement;		
	if (position.x < 0 ) {
		position.x = 0;
	} 
 }
    
    void MoveRight() {
	position.x += movement;
	if (position.x > GetScreenWidth() - image.width) {
		position.x = GetScreenWidth() - image.width;
	}   
}

    void FireLaser() {
		
	}

};

