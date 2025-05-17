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
    Texture2D map = LoadTexture("Backgrounds/worldmap.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.f};

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
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        // draw character
        knight.draw();

        // Check map boundaries
        Vector2 charPos = knight.getWorldPos();
        if (charPos.x < 0.f || charPos.y < 0.f ||
            charPos.x + windowWidth > mapScale * map.width ||
            charPos.y + windowHeight > mapScale * map.height)
        {
            knight.undoMovement();
        }



        EndDrawing();
    }
    
    UnloadTexture(map);
    CloseWindow();
    return 0;
}