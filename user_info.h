#pragma once
#include "raylib.h"

//class for score system 

class UI {
private:
   int score = 0;
public:
   UI() {}	
   void Update_Score(int points) {
	score += points;
}
   void Reset_Score() {
	score = 0;
}
   void Display_Score() {
	std::cout << "Score: " << score << std::endl;
	DrawText("SCORE", 20, 20, 30, WHITE);
	DrawText(TextFormat("%i", score), 130, 20, 30, GREEN);
}

};
