#include "raylib.h"
#include "raymath.h"
#include "Character.h"
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

    //Prop instance
    Prop rock{Vector2{0.f,0.f},LoadTexture("nature_tileset/Rock.png")};

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

        //render prop
        rock.Render(knight.getWorldPos());



        //chiharu
        DrawText("Chiharu",windowWidth/2.f-30,windowHeight/2.f-50,20,RED);

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