#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{

    // Pseudocode for Enemy Ai chasing main character
    // 1 get toTarget
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // 2 Normalize |to Target|
    toTarget = Vector2Normalize(toTarget);
    // 3 multiply |To Target| by speed
    toTarget = Vector2Scale(toTarget, speed);
    // 4 move Enemy (set worldPos)
    worldPos = Vector2Add(worldPos, toTarget);

    // for enemy location
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    BaseCharacter::tick(deltaTime);
}
