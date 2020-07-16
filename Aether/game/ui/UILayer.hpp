#pragma once
#include "oasis.h"

#include <vector>
#include <functional>

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
struct UIWindow;
struct UIElement
{
    enum class Type
    {
        TEXT = 0,
        TEXT_DYNAMIC,
        TEXTURE
    };

    Type m_type;
    union
    {
        struct {
            char * m_text;
            Oasis::Colour m_colour;
            UI::Font m_font;
        };
        struct {
            Oasis::Colour m_colour;
            UI::Font m_font;
        };
        struct {
            char * m_path;
            int m_width;
            int m_height;
        };
    };
    // This is used for dynamic text ONLY
    // Can't be put in union because of non-trivial destructor
    std::function<std::string(UIWindow&)> m_textFunction;

    // Static generator functions
    static UIElement CreateText(char * text, Oasis::Colour colour, UI::Font font);
    static UIElement CreateDynamicText(std::function<std::string(UIWindow&)> func, Oasis::Colour colour, UI::Font font);
    static UIElement CreateTexture(char * path, int width, int height);
};

////////////////////////////////////////////////////////////////
struct UIWindow
{
    enum class Alignment
    {
        TOP_LEFT = 0,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    bool m_show;
    Alignment m_alignment;
    int m_w;
    int m_h;
    int m_marginH;
    int m_marginV;
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

    // HELPER FUNCTIONS
    void AddResourceUI();
};