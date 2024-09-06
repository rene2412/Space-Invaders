#pragma once
#include "spaceships.h"
#include "obstacles.h"
#include "aliens.h"
#include "laser.h"
#include "mystery_ship.h"
#include "user_info.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Game {
private:
std::vector<Obstacle> obstacles;
std::vector<Alien> aliens; 
const float alien_speed = 0.5;
float offset_distance = 0.0;
bool movingRight = true;
bool movingDown = false;
bool alive = true;
SpaceShip spaceship;
Obstacle ob;
Alien a;
MysteryShip mystery;
UI info;
std::thread MysteryShipThread;
public:

Game() { 
        MysteryShipThread = std::thread(&MysteryShip::Run, &mystery);
	Alien::LoadTextures();
	MakeAliens();
	Make_Obstacles();
}

~Game() {
	Alien::UnloadTextures();
	mystery.Stop();
	if (MysteryShipThread.joinable()) {
		MysteryShipThread.join();	
	}
}


void Update_Game() {
	for (auto& laser : spaceship.Get_Lasers()) {
		laser.Update_SpaceShip_Laser();
	}
	cleanup_lasers();

    for (auto& alien : aliens) {
	for (auto& laser: alien.Get_Alien_Lasers()) {
		laser.Update_Alien_Laser();
	}
   }
	mystery.Move();
	Destroy_Mystery();
	Collision_Detection();
	Move_Aliens();
	AlienCombat();
	Destroy_SpaceShip();
	Destroy_Alien();
	cleanup_alien_lasers();
	Win_Screen();
	Death_Screen();

} 

void Make_Obstacles() {
   std::vector<std::vector<int>> grid = {
          {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
          {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
          {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
          {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
   };
        // Define the initial position for the first obstacle
          Vector2 initialPosition = {80.0f, 600.0f};
          int blockSpacing = ob.GetBlockSize() * grid[0].size() + 100.0f;  // Adjust spacing based on grid size
          // Create multiple obstacles with different positions
          for (int i = 0; i < 4; i++) {
              Vector2 position = {initialPosition.x + i * blockSpacing, initialPosition.y};
              obstacles.push_back(Obstacle(position, grid));
          }
}

void Destroy_SpaceShip() {
	 for (auto &alien : aliens) {
		for (auto& laser : alien.Get_Alien_Lasers()) {
		//will get the rectangle of the alien lasers and the rectangle spaceship
		if (CheckCollisionRecs(laser.GetAlienLaser(), spaceship.GetSpaceShip())) {
			alive = false;
			std::cout << "You died\n";	
			laser.Deactivate();	
			spaceship.SetSpaceShipPosition({-40, -30});
			}	
		}		
	}
}

void Collision_Detection() {
	for (auto& obstacle : obstacles) {
            for (auto& laser : spaceship.Get_Lasers()) {
			obstacle.Check_Collision(laser);  // Use the Obstacle's Check_Collision method
		}
        } 
	
     for (auto& alien : aliens) {
	  for (auto& obstacle : obstacles) {
	     for (auto& laser : alien.Get_Alien_Lasers()) { 
            		obstacle.Check_Collision2(laser); 
		 }
	   }
     }
}

void AlienCombat() {
	//pick random aliens and fire lasers
	std::srand(std::time(NULL));
	int random_index = std::rand() % aliens.size();
	Alien& random_alien = aliens[random_index];
	random_alien.Fire_Laser();
}


void Move_Aliens() {
    bool collision_right_wall = false;
    bool collision_left_wall = false;

    if (!movingDown) {
        // Check for collisions with walls and move horizontally
        for (auto& alien : aliens) {
            if (movingRight) {
                alien.MoveXRight(alien_speed);
                if (alien.GetPosition().x + alien.Get_Alien_Width() >= 750) {
                    collision_right_wall = true;
                }
            } else {
                alien.MoveXLeft(alien_speed);
                if (alien.GetPosition().x <= 0) {
                    collision_left_wall = true;
                }
            }
        }
    }

    // Handle collision with the right wall
    if (collision_right_wall or collision_left_wall) {
        movingDown = true;
    }

    // Move aliens down and reset direction
    if (movingDown) {
        if (offset_distance < 10.0f) {
            for (auto& alien : aliens) {
                alien.MoveYDown(alien_speed);
            }
            offset_distance += alien_speed;
        } else {
            offset_distance = 0.0f;
            movingRight = !movingRight;  // Switch direction
            movingDown = false;  // Stop moving down
        }
    }
}


void Destroy_Alien() {
	for (auto alienIter = aliens.begin(); alienIter !=  aliens.end(); ) {
		bool alienHit = false;
		for (auto &laser : spaceship.Get_Lasers()) {
			if (CheckCollisionRecs(alienIter->Get_Alien_Rectangle(), laser.GetSpaceShipLaser())) {
				std::cout << "alien collision\n";
				laser.Deactivate();
				//remove alien that was hit
				alienIter = aliens.erase(alienIter);
				alienHit = true;
				info.Update_Score(20);
				break;
		}		
	   }
	if (!alienHit) {
		alienIter ++;
      }
  }
}

void Destroy_Mystery() {
		for (auto& laser : spaceship.Get_Lasers()) {
			if (CheckCollisionRecs(laser.GetSpaceShipLaser(), mystery.GetMysteryShip())) {
   				laser.Deactivate();
				info.Update_Score(100);  
				mystery.SetMysteryPosition({-mystery.GetWidth(), -mystery.GetHeight()});
				break;	
		}
	}
}

void MakeAliens() {
     const int SX = 50;
     const int SY = 50;	
   
     for (int row = 2; row < 7; row++) {
         for (int col = 0; col < 11; col++) {
              float x = SX + col * a.Get_Alien_Width();
              float y = SY + row * a.Get_Alien_Height();
              int type;
               if (row == 2) {
                    type = 1;
            } else if (row == 3 or row == 4) {
                    type = 2;
            } else {
                    type = 3;
                }
                aliens.push_back(Alien({x, y}, type));
            }
        }
}

void Draw() {
      spaceship.Draw();
      for (auto& laser : spaceship.Get_Lasers()) {
		laser.Draw();	
	}
      
      for (auto& obstacle : obstacles ) {
		obstacle.Draw();
	}

       for (auto& alien : aliens) {
		alien.Draw();
	}
	mystery.Draw();
	
info.Display_Score();
}	

void Input() {
     if (IsKeyDown(KEY_LEFT)) {
	     spaceship.MoveLeft();
     }
     else if (IsKeyDown(KEY_RIGHT)) {
	    spaceship.MoveRight();
     }
     else if (IsKeyPressed(KEY_SPACE)) {
	    spaceship.FireLaser();
    }
}

void cleanup_lasers() {
	for (auto iter = spaceship.Get_Lasers().begin(); iter != spaceship.Get_Lasers().end(); ) {
		if (!iter -> Is_Active()) {
			iter = spaceship.Get_Lasers().erase(iter);
		}
		else iter ++;
	}
   }

void cleanup_alien_lasers() {
	auto& lasers = a.Get_Alien_Lasers();
    for (auto iter = lasers.begin(); iter != lasers.end(); ) {
        if (!iter->Is_Active()) {
            iter = lasers.erase(iter);  // Remove inactive lasers
        } else {
            iter ++;  // Move to the next laser
        }	
      }
   }

void Reset_Game() {
 // Reset spaceship to the initial state
    spaceship.SetSpaceShipPosition({(GetScreenWidth() - spaceship.GetWidth()) / 2, GetScreenHeight() - spaceship.GetHeight()});
    
    spaceship.Get_Lasers().clear();
    aliens.clear();
    MakeAliens();  // Recreate the aliens at their starting positions
    obstacles.clear();
    mystery.SetMysteryPosition({780, 60});  // Reset mystery ship to its starting position
    Make_Obstacles();
    info.Reset_Score();  
    alive = true;  
    mystery.Reset();  
}

void Win_Screen() {
	if (aliens.size() == 0) {
		ClearBackground(BLACK);
		DrawText("YOU WON", 125, 325, 100, GREEN);
		if (IsKeyPressed(KEY_ENTER)) {
			Reset_Game();
			}		
		}
	}

void Death_Screen() {
	if (alive == false) {
		ClearBackground(BLACK);
		DrawText("YOU DIED", 125, 325, 100, RED);
		if (IsKeyPressed(KEY_ENTER)) {
			Reset_Game();
		}	
	   }
     }	  
};

