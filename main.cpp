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

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1 : facing right , -1:facing left
    float rightLeft{1.f};

    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    float updateTime{1.0f / 12.0f};
    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
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
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

int main()
{
    // window screen
    const int windowWidth = 385;
    const int windowHeight = 385;

    InitWindow(windowWidth, windowHeight, "Clashy Clash");
    SetTargetFPS(60);
    
    // LoadTextures background
    Texture2D background = LoadTexture("Backgrounds/worldmap.png");
    Vector2 bgPos{0, 0};

    //Character instance/object
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    while (!WindowShouldClose())
    {
        // delta time
        float dT = GetFrameTime();

        // Update game
        knight.tick(dT);
        bgPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // draw background
        DrawTextureEx(background, bgPos, 0.0f, 4.0f, WHITE);

        // draw character
        knight.draw();

        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}