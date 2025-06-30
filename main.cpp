#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    // window  screen
    const int windowWidth = 385;
    const int windowHeight = 385;

    InitWindow(windowWidth, windowHeight, "Clashy Clash");
    SetTargetFPS(60);

    // LoadTextures background
    Texture2D map = LoadTexture("Backgrounds/worldmap1.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.f};

    // Character instance/object
    Character knight{windowWidth, windowHeight};

    // Enemy instance/object
    Enemy goblin(Vector2{}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
    goblin.setTarget(&knight);

    // prop instance
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    while (!WindowShouldClose())
    {
        // delta time
        float dT = GetFrameTime();

        // Update game
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // draw background
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        // Draw the props
        for (auto Prop : props)
        {
            Prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive())// character not alive 
        {
            DrawText("Game Over",windowWidth/2-90,windowHeight/2,40,RED);
            EndDrawing();
            continue; // it will continue the game
        }
        else //character is alive
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()),0,5);
            DrawText(knightHealth.c_str(),1.f,0.f,40,RED);
        }

        // enemy functions
        goblin.tick(dT);

        // Check map boundaries
        knight.tick(dT);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // collision
        for (auto Prop : props)
        {
            if (CheckCollisionRecs(Prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(CheckCollisionRecs(goblin.GetCollisionRec(),knight.getCollisionWeapon())){
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
    return 0;
}