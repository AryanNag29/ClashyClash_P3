#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character: public BaseCharacter
{
public:
    virtual void tick(float deltaTime) override;
    Character(int winWidth, int winHeight);

private:

};
