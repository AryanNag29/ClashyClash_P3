#include "raylib.h"
#include "Character.h"
#include "raymath.h"
#include "BaseCharacter.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}



void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // window movement
    Vector2 direction{};

    if (IsKeyDown(KEY_A))
        direction.x -= 1.0f;

    if (IsKeyDown(KEY_D))
        direction.x += 1.0f;

    if (IsKeyDown(KEY_W))
        direction.y -= 1.0f;

    if (IsKeyDown(KEY_S))
        direction.y += 1.0f;

    if (Vector2Length(direction) != 0.0f)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed)); //here speed of character is also defined
        // if else ternary operator for if else statement
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }
}
