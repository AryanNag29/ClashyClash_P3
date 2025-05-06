#include "raylib.h"
#include "raymath.h"

int main()
{
    // window
    int windowDimension[2];
    windowDimension[0] = 385; // width
    windowDimension[1] = 385; // height

    InitWindow(windowDimension[0], windowDimension[1], "Clashy Clash");

    SetTargetFPS(60); // fps
    // LoadTextures background
    Texture2D background = LoadTexture("Backgrounds/worldmap.png");
    Vector2 bgPos{0, 0};
    float speed{4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        windowDimension[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0),
        windowDimension[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // window movement
        Vector2 direction{};

        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;

        if (IsKeyDown(KEY_D))
            direction.x += 1.0;

        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;

        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            bgPos = Vector2Subtract(bgPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        // draw background
        DrawTextureEx(background, bgPos, 0.0, 4.0, WHITE);
        // draw the char
        Rectangle source{0.f, 0.f, (float)knight.width / 6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        Vector2 origin{};
        DrawTexturePro(knight, source, dest, origin, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
}