#include "raylib.h"
#include "raymath.h"

class Enemy{
    public:
    Enemy(Vector2 pos,Texture2D idle_texture,Texture2D run_texture);
    Vector2 getWorldPos();
    void tick(float deltaTime);
    void undoMovement();
    void draw();
    Rectangle GetCollisionRec();


    private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};

    // mapbound check
    Vector2 worldPosLastFrame{};

    // width and height
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
    const float scale{4.f};
};