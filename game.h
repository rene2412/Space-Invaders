#pragma once
#include "spaceships.h"

class Game {
private:
 SpaceShip spaceship;

public:
  Game() {};
 ~Game() {};
 
void Draw() {
   spaceship.Draw();
}	

void Input() {
     if (IsKeyDown(KEY_LEFT)) {
	     spaceship.MoveLeft();
     }
     else if (IsKeyDown(KEY_RIGHT)) {
	    spaceship.MoveRight();
     }
}

};

