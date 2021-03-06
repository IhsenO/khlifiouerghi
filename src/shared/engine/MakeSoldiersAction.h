// Generated by dia2code
#ifndef ENGINE__MAKESOLDIERSACTION__H
#define ENGINE__MAKESOLDIERSACTION__H


namespace state {
  class State;
};
namespace engine {
  class Action;
}

#include "Action.h"

namespace engine {

  /// class MakeSoldiersAction - 
  class MakeSoldiersAction : public engine::Action {
    // Attributes
  protected:
    int x;
    int y;
    // Operations
  public:
    MakeSoldiersAction (int x, int y);
    void undo (state::State& state);
    // Setters and Getters
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
  };

};

#endif
