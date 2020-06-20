#include "oasis.h"

#include "gamelayer.hpp"
#include "camera/camera.hpp"
#include "select/select.hpp"
#include "debug/debugLayer.hpp"

class Game : public Oasis::GameState
{
public:
    virtual void InitLayers() override
    {
        // Layers are added bottom -> top
        // TODO: Event handling should also be handled top to bottom
        // AddLayer(new Background());
        AddLayer(new Camera());
        AddLayer(new GameLayer());
        AddLayer(new SelectLayer());
        // AddLayer(new UILayer());
        // AddLayer(new AlertLayer());
        AddLayer(new DebugLayer());
    }
private:
    
};