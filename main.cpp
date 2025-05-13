#include "raylib.h"
#include "raymath.h"
#include "Character.h"


int main()
{
    // window  screen

    const int windowWidth = 385;
    const int windowHeight = 385;

    InitWindow(windowWidth, windowHeight, "Clashy Clash");
    SetTargetFPS(60);
    
    // LoadTextures background
    Texture2D background = LoadTexture("Backgrounds/worldmap.png");
    Vector2 mapPos{0, 0};

    //Character instance/object
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    while (!WindowShouldClose())
    {
        // delta time
        float dT = GetFrameTime();

        // Update game
        knight.tick(dT);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // draw background
        DrawTextureEx(background, mapPos, 0.0f, 4.0f, WHITE);

        // draw character
        knight.draw();

        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}