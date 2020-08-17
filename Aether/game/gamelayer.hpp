#pragma once
#include "oasis.h"

#include <vector>
#include <string>

#include "game/background/background.hpp"

class Entity;

////////////////////////////////////////////////////////////////
// Use a custom render system for more control on rendering
struct RenderItem
{
    enum class Type
    {
        SPRITE,
        LINE,
        CIRCLE,
        RECT,
        RECT_FILLED,
    };
    Type m_type;
    float m_x;
    float m_y;
    int m_z;
    float m_alpha;
    Oasis::Colour m_colour;
    union {
        struct {
            Oasis::Sprite * m_sprite;
        };
        struct {
            float m_x2;
            float m_y2;
        };
        struct {
            float m_radius;
        };
        struct {
            float m_width;
            float m_height;
        };
    };
};

////////////////////////////////////////////////////////////////
class GameService
{
public:
    static void AddEntity(Entity * entity);
    static std::vector<Entity *>& GetEntities();

    static void DrawSprite(Oasis::Sprite * sprite, int z = 0);
    static void DrawLine(float x1, float y1, float x2, float y2, int z = 0, const Oasis::Colour& colour = Oasis::Colours::RED);
    static void DrawCircle(float x, float y, float radius, int z = 0, const Oasis::Colour& colour = Oasis::Colours::RED);
    static void DrawRect(float x, float y, float w, float h, int z = 0, const Oasis::Colour& colour = Oasis::Colours::RED);
    static void DrawRectFilled(float x, float y, float w, float h, int z = 0, const Oasis::Colour& colour = Oasis::Colours::RED, float alpha = 1.f);

    static void Select(Ref<Entity> entity);
    static bool Selected(Ref<Entity> entity);
    static Ref<Entity> GetSelected();

    static void SetMoveAction();
    static void SetTransferAction();
    static void SetDeployAction();
private:
    friend class GameLayer;
    static Ref<GameLayer> s_gameLayer;
};

////////////////////////////////////////////////////////////////
class GameLayer : public Oasis::GameStateLayer
{
    friend class GameService;
public:
    GameLayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;

    void DrawItem(RenderItem item) { m_renderItems.emplace_back(item); }
private:
    std::vector<Entity *> m_entities;
    std::vector<RenderItem> m_renderItems;

    Ref<Entity> m_selected;
    enum class UserActionState
    {
        NONE = 0,
        MOVE,
        TRANSFER,
        DEPLOY
    };
    UserActionState m_userActionState;

    Background m_background;
};