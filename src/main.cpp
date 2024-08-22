#include <math.h>
#include <functional>

#include "flecs.h"

#include "raylib.h"
#include "raymath.h"

struct Position
{
    float x;
    float y;
};

struct Vector2LerpComponent
{
    Position start;
    Position destination;
    std::function<float(float)> ease;
    float duration;
    float elapsedTime;
};

struct CircleBody
{
    int radius;
    Color color;
};

float EaseInOutSine(float i)
{
    return -(cos(PI * i) - 1) / 2;
}

float EaseLinear(float i) { return i; }

int main()
{
    flecs::world world;

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "messing around");

    SetTargetFPS(60);

    auto player = world.entity("player");

    player.set<Position>({.x{100}, .y{100}});
    player.set<CircleBody>({.radius{40}, .color{RED}});

    Vector2LerpComponent l{.start{.x{player.get<Position>()->x}, .y{player.get<Position>()->y}},
                           .destination{.x{player.get<Position>()->x + 200}, .y{player.get<Position>()->y + 200}},
                           .ease{EaseLinear},
                           .duration{2}};

    player.set<Vector2LerpComponent>(l);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        auto lerpPositionQuery = world.query<Position, Vector2LerpComponent>();

        lerpPositionQuery.each([deltaTime](Position &position, Vector2LerpComponent &vector2LerpComponent)
                               {
                                   // if (vector2LerpComponent.elapsedTime > vector2LerpComponent.duration) {
                                   //     entity.remove<Vector2LerpComponent>();
                                   // }
                                   // else {
                                   vector2LerpComponent.elapsedTime += deltaTime;
                                   float progress = 1.0f - std::pow(vector2LerpComponent.elapsedTime / vector2LerpComponent.duration, deltaTime);
                                   Vector2 newPosition = Vector2Lerp({position.x, position.y},
                                                                     {vector2LerpComponent.destination.x, vector2LerpComponent.destination.y},
                                                                     vector2LerpComponent.ease(progress));
                                   position.x = newPosition.x;
                                   position.y = newPosition.y;
                                   // } });
                               });

        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto drawQuery = world.query<const Position, const CircleBody>();
        drawQuery.each([](const Position &position, const CircleBody &body)
                       { DrawCircle(position.x, position.y, body.radius, body.color); });

        EndDrawing();
    }

    return 0;
}
