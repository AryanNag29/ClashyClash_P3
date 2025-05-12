#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void draw();
    Character();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};

    //width and height
    float width{};
    float height{};
    
    // 1 : facing right , -1:facing left
    float rightLeft{1.f};

    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    float updateTime{1.0f / 12.0f};
    const float speed{4.f};
};

