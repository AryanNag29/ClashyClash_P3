#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"

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

    //Enemy instance/object
    Enemy enemy(Vector2{},LoadTexture("characters/goblin_idle_spritesheet.png"),LoadTexture("characters/goblin_run_spritesheet.png"));
    

   //prop instance
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };


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

        //Draw the props
        for(auto Prop : props){
            Prop.Render(knight.getWorldPos());
        }
        // draw character
        knight.draw();
        //enemy functions
        enemy.tick(dT);
        enemy.draw();


        // Check map boundaries
        Vector2 charPos = knight.getWorldPos();
        if (charPos.x < 0.f || charPos.y < 0.f ||
            charPos.x + windowWidth > mapScale * map.width ||
            charPos.y + windowHeight > mapScale * map.height)
        {
            knight.undoMovement();
        }

        //collision
        for(auto Prop : props){
            if(CheckCollisionRecs(Prop.GetCollisionRec(knight.getWorldPos()),knight.GetCollisionRec())){
                knight.undoMovement();
            }
        }



        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
    return 0;
}