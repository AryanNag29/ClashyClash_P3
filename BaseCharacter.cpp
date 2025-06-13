#include "BaseCharacter.h"
#include "raylib.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() :
    texture(LoadTexture("characters/knight_idle_spritesheet.png")),
    idle(LoadTexture("characters/knight_idle_spritesheet.png")),
    run(LoadTexture("characters/knight_run_spritesheet.png"))
{
}

void BaseCharacter::draw()
{
    Rectangle source{frame * static_cast<float>(texture.width) / 6.f, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
 
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
