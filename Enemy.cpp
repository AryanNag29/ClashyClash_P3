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
    // 1 get velocity
    velocity = Vector2Subtract(target->getScreenPos(), screenPos);
    // 2 Normalize |to Target|
    // 3 multiply |To Target| by speed
    // 4 move Enemy (set worldPos)
    // for enemy location
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    //run animation for enemy
    BaseCharacter::tick(deltaTime);


}
