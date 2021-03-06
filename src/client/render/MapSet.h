// Generated by dia2code
#ifndef RENDER__MAPSET__H
#define RENDER__MAPSET__H

#include <vector>
#include <string>

namespace render {
  class Tile;
};
namespace state {
  class Element;
};
namespace render {
  class TileSet;
}

#include "Tile.h"
#include "TileSet.h"

namespace render {

  /// class MapSet - 
  class MapSet : public render::TileSet {
    // Attributes
  protected:
    std::vector<Tile> map;
    // Operations
  public:
    MapSet ();
    const std::string getFile () const;
    int getWidth () const;
    int getHeight () const;
    const Tile& getTile (const state::Element& e) const;
    // Setters and Getters
    const std::vector<Tile>& getMap() const;
    void setMap(const std::vector<Tile>& map);
  };

};

#endif
