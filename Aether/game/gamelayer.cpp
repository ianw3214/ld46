#include "gamelayer.hpp"
#include "entity/entity.hpp"

////////////////////////////////////////////////////////////
#include "entity/component.hpp"
#include "entity/components/renderComponent.hpp"
class TestComponent : public Component
{
public:
    TestComponent(Ref<Entity> entity) : Component(entity) {}
    virtual void Update(float delta) override { Oasis::Console::AddLog("TEST"); }
};
////////////////////////////////////////////////////////////

Ref<GameLayer> GameService::s_gameLayer = nullptr;

void GameService::AddEntity(Entity * entity)
{
    s_gameLayer->m_entities.push_back(entity);
}

GameLayer::GameLayer()
{
    GameService::s_gameLayer = this;
}

void GameLayer::Init()
{
    ////////////////////////////////////////////////////////////
    Entity * test = new Entity();
    test->SetX(30.f);
    test->SetY(30.f);
    test->AddComponent(new TestComponent(test));
    test->AddComponent(new RenderComponent(test, "res/sprites/scout.png", 200.f, 200.f));
    GameService::AddEntity(test);
    ////////////////////////////////////////////////////////////
}

void GameLayer::Close()
{

}

bool GameLayer::HandleEvent(const Oasis::Event& event)
{
    return false;
}

void GameLayer::Update()
{
    // Microseconds to seconds
    float delta = Oasis::WindowService::GetDeltaF() / 1000000.f;
    for (Ref<Entity> entity : m_entities)
    {
        entity->Update(delta);
    }
}