// Generated by dia2code
#ifndef RENDER__RENDERLAYER__H
#define RENDER__RENDERLAYER__H


namespace render {
  class TileSet;
  class Drawer;
}

#include "TileSet.h"
#include "Drawer.h"

namespace render {

  /// class RenderLayer - 
  class RenderLayer {
    // Associations
    // Attributes
  public:
    TileSet* tileSet;
  protected:
    Drawer* drawer;
    // Operations
  public:
    virtual ~RenderLayer ();
    virtual void initDrawer () = 0;
    Drawer* getDrawer () const;
    void setDrawer (Drawer* drawer);
    // Setters and Getters
  };

};

#endif