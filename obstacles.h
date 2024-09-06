#pragma once
#include <vector>
#include "block.h"
#include "laser.h"
#include "raylib.h"
class Obstacle {
private:
	Vector2 position; 
	std::vector<std::vector<int>> grid;
	const int BlockSize = 3;
public:
	Obstacle() {}
	
	Obstacle(Vector2 P, const std::vector<std::vector<int>>& g) : position(P), grid(g)  {}
	
	Vector2 GetPosition() const { return position; }
	
	int GetBlockSize() const { return BlockSize; } 

	void Check_Collision(Laser &laser) {
         	for (unsigned int row = 0; row < grid.size(); row++) {
       	    		for (unsigned int col = 0; col < grid[row].size(); col++) {
            			if (grid[row][col] == 1) {  // If the block exists
                		float x = position.x + col * static_cast<float>(BlockSize);
                		float y = position.y + row * static_cast<float>(BlockSize);
	    	            	Rectangle blockRect = { x, y, static_cast<float>(BlockSize), static_cast<float>(BlockSize) };
					if (CheckCollisionRecs(laser.GetSpaceShipLaser(), blockRect)) {
                    			 grid[row][col] = 0;  // Destroy the block
                    			 laser.Deactivate(); 
                   			 return;  // Exit after one collision is detected
	     			}
         		}
     		}
	}
}	
	void Check_Collision2(Laser &laser) {
         	for (unsigned int row = 0; row < grid.size(); row++) {
       	    		for (unsigned int col = 0; col < grid[row].size(); col++) {
            			if (grid[row][col] == 1) {  // If the block exists
                		float x = position.x + col * static_cast<float>(BlockSize);
                		float y = position.y + row * static_cast<float>(BlockSize);
	    	            	Rectangle blockRect = { x, y, static_cast<float>(BlockSize), static_cast<float>(BlockSize) };
					if (CheckCollisionRecs(laser.GetAlienLaser(), blockRect)) {
                   			 //std::cout << "Collision detected\n";
                    			 grid[row][col] = 0;  // Destroy the block
                    			 laser.Deactivate(); 
                   			 return;  // Exit after one collision is detected
	     			}
         		}
     		}
	}
}
	void Draw() {
		for (unsigned int row = 0; row < grid.size(); row++) {
			for (unsigned col = 0; col < grid[0].size(); col ++) {
				if (grid[row][col] == 1) {
					float x = position.x + col * BlockSize;
					float y = position.y + row * BlockSize;
					DrawRectangle(x, y, BlockSize, BlockSize, GOLD);
				} 
	     		}		
		}
   	}   
   
	 
}; 
   

