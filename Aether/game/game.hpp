#include "oasis.h"

#include "debugLayer/debugLayer.hpp"

class Game : public Oasis::GameState
{
public:
    virtual void InitLayers() override
    {
        // Layers are added bottom -> top
        AddLayer(new DebugLayer());
    }
private:
};