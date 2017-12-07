// Generated by dia2code
#ifndef ENGINE__ARMYFUSIONACTION__H
#define ENGINE__ARMYFUSIONACTION__H


namespace state {
  class State;
};
namespace engine {
  class Action;
}

#include "Action.h"

namespace engine {

  /// class ArmyFusionAction - 
  class ArmyFusionAction : public engine::Action {
    // Attributes
  protected:
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
    int soldiersA;
    int soldiersB;
    // Operations
  public:
    ArmyFusionAction (int xFrom, int yFrom, int xTo, int yTo, int soldiersA, int soldiersB);
    void undo (state::State& state);
    // Setters and Getters
    int getXFrom() const;
    void setXFrom(int xFrom);
    int getYFrom() const;
    void setYFrom(int yFrom);
    int getXTo() const;
    void setXTo(int xTo);
    int getYTo() const;
    void setYTo(int yTo);
    int getSoldiersA() const;
    void setSoldiersA(int soldiersA);
    int getSoldiersB() const;
    void setSoldiersB(int soldiersB);
  };

};

#endif