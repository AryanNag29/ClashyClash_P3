#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    virtual void tick(float deltaTime) override;
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
};

#endif