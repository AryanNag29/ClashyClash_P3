#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character: public BaseCharacter
{
public:
    void tick(float deltaTime);

    Character(int winWidth, int winHeight);

private:

};
