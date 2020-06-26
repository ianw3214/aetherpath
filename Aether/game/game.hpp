#include "oasis.h"

#include "gamelayer.hpp"
#include "camera/camera.hpp"
#include "ui/UILayer.hpp"
#include "debug/debugLayer.hpp"

class Game : public Oasis::GameState
{
public:
    virtual void CreateLayers() override
    {
        // Layers are added bottom -> top
        // AddLayer(new Background());
        AddLayer(new GameLayer());
        AddLayer(new Camera());
        AddLayer(new UILayer());
        // AddLayer(new AlertLayer());
        AddLayer(new DebugLayer());
    }
private:
    
};