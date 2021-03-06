#include "map.hpp"

#include <random>

#include "game/gamelayer.hpp"

#include "game/entity/entity.hpp"
#include "game/entity/components/renderComponent.hpp"
#include "game/entity/components/collisionComponent.hpp"
#include "game/entity/components/moveComponent.hpp"
#include "game/entity/components/resourceComponent.hpp"
#include "game/entity/components/goalComponent.hpp"
#include "game/entity/components/hangarComponent.hpp"

void Map::GenerateMap()
{
    GenerateEarth();
    GenerateMoon();
    GeneratePlanets();
    GenerateAsteroids();
    GenerateGoalPlanet();

    /////////////////////////////////////////////////////////
    // DEBUG SHIP
    Entity * ship = new Entity();
    ship->SetX(400.f);
    ship->SetY(400.f);
    ship->AddComponent(new RenderComponent(ship, "res/sprites/scout.png", 130.f, 80.f));
    ship->AddComponent(new CollisionComponent(ship, Shape::GenerateRect(130.f, 80.f, -60.f, -40.f)));
    ship->AddComponent(new ResourceComponent(ship, 100, 100, 100, 100));
    ship->AddComponent(new MoveComponent(ship));
    GameService::AddEntity(ship);
    /////////////////////////////////////////////////////////
}

void Map::GenerateEarth()
{
    Entity * earth = new Entity();
    earth->SetX(0.f);
    earth->SetY(0.f);
    earth->AddComponent(new RenderComponent(earth, "res/sprites/earth.png", 400.f, 400.f));
    earth->AddComponent(new CollisionComponent(earth, Shape::GenerateCircle(200.f)));
    earth->AddComponent(new ResourceComponent(earth, 100, 100, 100, 100));
    earth->AddComponent(new HangarComponent(earth));
    // earth->AddComponent(new MoveComponent(earth));
    GameService::AddEntity(earth);
}

void Map::GenerateMoon()
{
    Entity * moon = new Entity();
    moon->SetX(400.f);
    moon->SetY(-400.f);
    // TODO: Need actual moon sprite
    moon->AddComponent(new RenderComponent(moon, "res/sprites/earth.png", 200.f, 200.f));
    moon->AddComponent(new CollisionComponent(moon, Shape::GenerateCircle(100.f)));
    moon->AddComponent(new ResourceComponent(moon, 100, 100, 100, 100));
    // moon->AddComponent(new MoveComponent(moon));
    GameService::AddEntity(moon);
}

void Map::GeneratePlanets()
{
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-40000, 40000);

    for (unsigned int i = 0; i < NUM_PLANETS; ++i)
    {
        const float x = static_cast<float>(position_dist(el));
        const float y = static_cast<float>(position_dist(el));

        Entity * planet = new Entity();
        planet->SetX(x);
        planet->SetY(y);
        // TODO: Need actual planet sprites
        planet->AddComponent(new RenderComponent(planet, "res/sprites/planets/planet1.png", 300.f, 300.f));
        planet->AddComponent(new CollisionComponent(planet, Shape::GenerateCircle(150.f)));
        planet->AddComponent(new ResourceComponent(planet, 100, 100, 100, 100));
        GameService::AddEntity(planet);
    }
}

void Map::GenerateAsteroids()
{
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-40000, 40000);

    for (unsigned int i = 0; i < NUM_ASTEROIDS; ++i)
    {
        const float x = static_cast<float>(position_dist(el));
        const float y = static_cast<float>(position_dist(el));

        Entity * asteroid = new Entity();
        asteroid->SetX(x);
        asteroid->SetY(y);
        // TODO: Need actual asteroid sprites
        asteroid->AddComponent(new RenderComponent(asteroid, "res/sprites/asteroid.png", 120.f, 120.f));
        asteroid->AddComponent(new CollisionComponent(asteroid, Shape::GenerateCircle(60.f)));
        asteroid->AddComponent(new ResourceComponent(asteroid, 100, 100, 100, 100));
        GameService::AddEntity(asteroid);
    }
}

void Map::GenerateGoalPlanet()
{
    std::random_device r;
    std::default_random_engine el(r());
    // Generate the goal planet close for now for debug purposes
    std::uniform_int_distribution<int> position_dist(-2000, 2000);

    const float x = static_cast<float>(position_dist(el));
    const float y = static_cast<float>(position_dist(el));

    Entity * goal = new Entity();
    goal->SetX(x);
    goal->SetY(y);
    // TODO: Need actual asteroid sprites
    goal->AddComponent(new RenderComponent(goal, "res/sprites/planets/goal.png", 420.f, 420.f));
    goal->AddComponent(new CollisionComponent(goal, Shape::GenerateCircle(210.f)));
    goal->AddComponent(new ResourceComponent(goal, 100, 100, 100, 100));
    goal->AddComponent(new GoalComponent(goal));
    GameService::AddEntity(goal);
}