#pragma once
#include "oasis.h"

#include <vector>

////////////////////////////////////////////////////////////////
namespace UI
{
    enum class Font
    {
        DEFAULT = 0,
        SMALL
    };
    inline int GetFontSize(Font font)
    {
        if (font == Font::DEFAULT) return 32;
        if (font == Font::SMALL) return 16;
        return 0;
    }
    inline std::string GetFont(Font font)
    {
        if (font == Font::DEFAULT) return "default";
        if (font == Font::SMALL) return "small";
        return "";
    }
    inline std::string GetFontPath(Font font)
    {
        if (font == Font::DEFAULT) return "res/fonts/ProggyClean.ttf";
        if (font == Font::SMALL) return "res/fonts/ProggyClean.ttf";
        return "";
    }
}

////////////////////////////////////////////////////////////////
struct UIElement
{
    enum class Type
    {
        TEXT = 0
    };

    Type m_type;
    union
    {
        struct {
            // TODO: Allow format strings
            // probably want to use std::format
            char * m_text;
            Oasis::Colour m_colour;
            UI::Font m_font;
        };
    };
};

////////////////////////////////////////////////////////////////
struct UIWindow
{
    bool m_show;
    // TODO: Use alignments w/ padding and margin instead of direct pos
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    // UI Window styling
    Oasis::Colour m_background;
    Oasis::Colour m_borderColour;
    unsigned int m_borderWidth;
    // UI Elements from top to bottom
    std::vector<UIElement> m_elements;
};

////////////////////////////////////////////////////////////////
class UIService
{
    friend class UILayer;
    static Ref<UILayer> s_UILayer;
public:
    static void AddUIWindow(UIWindow window);
};

////////////////////////////////////////////////////////////////
class UILayer : public Oasis::GameStateLayer
{
    friend class UIService;
public:
    UILayer();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;
private:
    std::vector<UIWindow> m_windows;
};