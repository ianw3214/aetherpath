#include "oasis.h"

#include "UILayer/UILayer.hpp"
#include "gameLayer/gameLayer.hpp"
#include "background/background.hpp"
#include "camera/camera.hpp"
#include "debugLayer/debugLayer.hpp"

class Game : public Oasis::GameState
{
public:
    virtual void InitLayers() override
    {
        // Layers are added bottom -> top
        AddLayer(new Background());
        AddLayer(new GameLayer());
        AddLayer(new Camera());
        AddLayer(new UILayer());
        AddLayer(new DebugLayer());
    }
private:
    
};