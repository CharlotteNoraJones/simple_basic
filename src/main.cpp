#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

float EaseInOutSine(float i)
{
    return -(cos(PI * i) - 1) / 2;
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "messing around");

    Vector2 center = {.x{400}, .y{200}};

    float duration{1.5f};

    float timeElapsed{0.0f};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (timeElapsed < duration)
        {
            float t{timeElapsed / duration};
            center.y = Lerp(100, 400, EaseInOutSine(t));
            timeElapsed += GetFrameTime();
        }
        else
        {
            center.y = 400;
        }

        ClearBackground(RAYWHITE);

        DrawCircle(center.x, center.y, 100, RED);

        EndDrawing();
    }

    return 0;
}
