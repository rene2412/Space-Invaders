#pragma once 
#include <vector>
#include "raylib.h"

class Block {
private:
	Vector2 position;
	Rectangle block;	
public:
	Block(Vector2 P) : position(P) {
		block = { position.x, position.y, 3, 3 };
	} 
	
	Vector2 GetPosition() const { return position; }	

	Rectangle GetBlock() { return block; } 	

	void Draw () {
		DrawRectangle(position.x, position.y, 3, 3, GREEN); 	
	 }
};
