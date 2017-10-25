// Generated by dia2code
#ifndef RENDER__MAPLAYER__H
#define RENDER__MAPLAYER__H


namespace state {
  class Layer;
};
namespace render {
  class RenderLayer;
}

#include "RenderLayer.h"
#include "state/Layer.h"

namespace render {

  /// class MapLayer - 
  class MapLayer : public render::RenderLayer {
    // Associations
    // Attributes
  protected:
    const state::Layer& tab;
    // Operations
  public:
    MapLayer (const state::Layer& tab);
    void initDrawer ();
    // Setters and Getters
    const state::Layer& getTab() const;
  };

};

#endif
