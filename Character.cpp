#include "raylib.h"
#include "Character.h"
#include "raymath.h"

Character::Character(){
    width = texture.width/maxFrame;
    height = texture.height;

}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
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
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
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

void Character::draw()
{
    // draw the char
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

void Character::undoMovement(){
    worldPos = worldPosLastFrame;
}
