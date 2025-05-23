#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy :: Enemy(Vector2 pos,Texture2D idle_texture, Texture2D run_texture) :
worldPos(pos),
texture(idle_texture),
idle(idle_texture),
run(run_texture)
{
    width = texture.width / maxFrame;
    height = texture.height;

}

void Enemy :: tick(float deltaTime){
    worldPosLastFrame = worldPos;//for undo movement
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

void Enemy::draw()
{
    // draw the char
    Rectangle source{frame * static_cast<float>(texture.width) / 6.f, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

void Enemy::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::GetCollisionRec(){
        return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};

}