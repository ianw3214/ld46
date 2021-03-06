#include "renderComponent.hpp"
#include "game/entity/entity.hpp"

#include "game/gamelayer.hpp"
#include "game/camera/camera.hpp"

RenderComponent::RenderComponent(Ref<Entity> entity, const std::string& path, float width, float height)
    : Component(entity)
    , m_sprite(path)
    , m_width(width)
    , m_height(height)
{
    // If no set width/height, use the width/height of the sprite
    if (width == 0.f && height == 0.f)
    {
        m_width = m_sprite.GetWidth();
        m_height = m_sprite.GetHeight();
    }
}

void RenderComponent::Update(float delta)
{
    const float scale = CameraService::GetScale();
    const float window_width = static_cast<float>(Oasis::WindowService::WindowWidth());
    const float window_height = static_cast<float>(Oasis::WindowService::WindowHeight());
    const float width = m_width * scale;
    const float height = m_height * scale;
    // Have the sprite rendered cenetered around it's middle point
    const float screen_x = CameraService::RawToScreenX(m_entityRef->GetX() - m_width / 2);
    const float screen_y = CameraService::RawToScreenY(m_entityRef->GetY() - m_height / 2);
    if (screen_x > -width && screen_x < window_width && screen_y > -height && screen_y < window_height)
    {
        // Render
        m_sprite.SetPos(screen_x, screen_y);
        m_sprite.SetDimensions(width, height);
        bool selected = GameService::Selected(m_entityRef);
        m_sprite.SetTint(Oasis::Colours::WHITE, static_cast<float>(selected) * 0.2f);
        GameService::DrawSprite(&m_sprite, 0);
    }
}

RenderComponent* RenderComponent::LoadFromJson(const json& data, Ref<Entity> entity)
{
    // TODO: Add an error image to make it clear when something is wrong
    std::string path = "";
    float width = 100.f;
    float height = 100.f;
    if (data.find("path") != data.end() && data["path"].is_string())
    {
        path = data["path"];
    }
    if (data.find("width") != data.end() && data["width"].is_number_float())
    {
        width = data["width"];
    }
    if (data.find("height") != data.end() && data["height"].is_number_float())
    {
        height = data["height"];
    }
    return new RenderComponent(entity, path, width, height);
}