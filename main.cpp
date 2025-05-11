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

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right , -1:facing left
    float rightLeft{1.f};
    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    float updateTime{1.0f / 12.0f};
    const float speed{4.f};
};

void Character ::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}
void Character ::tick(float deltaTime)
{
    // window movement
    Vector2 direction{};

    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;

    if (IsKeyDown(KEY_D))
        direction.x += 1.0;

    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;

    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // if else turnery operator for if else statement
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

int main()
{
    // window screen
    int windowDimension[2];
    windowDimension[0] = 385; // width
    windowDimension[1] = 385; // height

    InitWindow(windowDimension[0], windowDimension[1], "Clashy Clash");

    SetTargetFPS(60); // fps
    // LoadTextures background
    Texture2D background = LoadTexture("Backgrounds/worldmap.png");
    Vector2 bgPos{0, 0};
    float speed{4.0};
    // load Texture
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");

    Vector2 knightPos{
        (float)windowDimension[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0),
        (float)windowDimension[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)};

    // 1 : facing right , -1:facing left
    float rightLeft{1.f};

    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    float updateTime{1.0f / 12.0f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time
        float dT{GetFrameTime()};

        // draw background
        DrawTextureEx(background, bgPos, 0.0, 4.0, WHITE);

        // draw the char
        Rectangle source{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        Vector2 origin{};
        DrawTexturePro(knight, source, dest, origin, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
}