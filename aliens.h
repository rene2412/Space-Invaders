#pragma once
#include "raylib.h"
#include <vector>
#include "laser.h"

class Alien {
private:
    Vector2 position;
    Rectangle enemy_aliens;
    std::vector<Laser> alien_lasers;
    static Texture2D texture1;
    static Texture2D texture2;
    static Texture2D texture3;
    int Alien_Width = 55;
    int Alien_Height = 55;
    int alien_laser_speed = 7;
    int type;
    float lastFireTime = 0.0f;
    float fireCoolDown = 0.5f;
    int points;
public:

  Alien() {} 
 
  Alien(Vector2 p, int t) : position(p), type(t) {
		enemy_aliens = { position.x, position.y, static_cast<float>(Alien_Width), static_cast<float>(Alien_Height) };
	}
    
  // Static method to load textures (only once)
    static void LoadTextures() {
        texture1 = LoadTexture("images/alien_1.png");
        texture2 = LoadTexture("images/alien_2.png");
        texture3 = LoadTexture("images/alien_3.png");
    }

    // Static method to unload textures
    static void UnloadTextures() {
        UnloadTexture(texture1);
        UnloadTexture(texture2);
        UnloadTexture(texture3);
    }
  
  int GetAlienPoints() const { return points; }
  Vector2 GetPosition() const { return position; }
  void SetPosition(Vector2 newPos) { position = newPos; } 

  int Get_Alien_Width() const { return Alien_Width; }
  int Get_Alien_Height() const { return Alien_Height; }

   Rectangle Get_Alien_Rectangle() const { return enemy_aliens; } 
   std::vector<Laser>& Get_Alien_Lasers() { return alien_lasers; }
 
   void MoveXRight(float posX) {
	position.x += posX;
	enemy_aliens.x = position.x;
   }
   void MoveXLeft(float posX) {
	position.x -= posX;
	enemy_aliens.x = position.x;
   }
   void MoveYDown(float posY) {
	position.y += posY;
	enemy_aliens.y = position.y;
   }

   Color OVERRIDE = {255, 255, 255, 255 };

   void Draw() {
	   Texture2D textureToDraw;
	   switch (type) {
            case 1:
                textureToDraw = texture1;
                break;
            case 2:
                textureToDraw = texture2;
                break;
            case 3:
                textureToDraw = texture3;
                break;
    		}
        DrawTextureV(textureToDraw, position,  SKYBLUE);
	for (auto& laser : alien_lasers) {
		laser.Draw();
	}  

}

   void Fire_Laser() {
 	if (GetTime() - lastFireTime >= fireCoolDown)  {
 	      alien_lasers.push_back(Laser({position.x + (Alien_Width / 2) - 2, position.y + Alien_Height}, alien_laser_speed, true));	
		lastFireTime = GetTime();
		}
	}


};
Texture2D Alien::texture1;
Texture2D Alien::texture2;
Texture2D Alien::texture3;

