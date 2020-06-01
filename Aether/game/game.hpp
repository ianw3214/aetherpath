#include "oasis.h"

#include "gamelayer.hpp"
#include "camera/camera.hpp"


class Game : public Oasis::GameState
{
public:
    virtual void InitLayers() override
    {
        // Layers are added bottom -> top
        // AddLayer(new Background());
        AddLayer(new Camera());
        AddLayer(new GameLayer());
        // AddLayer(new UILayer());
        // AddLayer(new AlertLayer());
        // AddLayer(new DebugLayer());
    }
private:
    
};