#include "raylib.h"
#include "raymath.h"
#include "Prop.h"
//prop constructor
Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos),
                                         texture(tex)
{
}
//draw prop
void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}
//collision of prop
Rectangle Prop ::GetCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    //to make prop rec small
    float padW{20.f};
    float padH{40.f};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale -padW,
        texture.height * scale -padH};
}