#include "raylib.h"
#include "game.h"
int main() {
    //750x700 grid
    const int screenWidth = 750;
    const int screenHeight = 700;
    // Get the screen width and height
    int screenCenterX = GetMonitorWidth(0) / 2;
    int screenCenterY = GetMonitorHeight(0) / 2;
    // Calculate the position of the top-left corner of the window to center it
    int windowPosX = screenCenterX - (screenWidth / 2);
    int windowPosY = screenCenterY - (screenHeight / 2);
    //open the window and set the grid parameters and title it 
    InitWindow(screenWidth, screenHeight, "Space Inavders");
    SetWindowPosition(windowPosX, windowPosY);
    SetTargetFPS(60); //Set our game to run at 60 frames-per-second
    Color grey = {29, 29, 27, 255};
    Game game;

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
      //handle keybaord input (left and right) 
       game.Input(); 
       //Draw a canvas
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
	EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

