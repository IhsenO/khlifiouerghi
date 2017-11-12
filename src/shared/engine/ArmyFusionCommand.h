// Generated by dia2code
#ifndef ENGINE__ARMYFUSIONCOMMAND__H
#define ENGINE__ARMYFUSIONCOMMAND__H


namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "CommandTypeId.h"
#include "Command.h"

namespace engine {

  /// class ArmyFusionCommand - 
  class ArmyFusionCommand : public engine::Command {
    // Attributes
  protected:
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
    // Operations
  public:
    ArmyFusionCommand (int xFrom, int yFrom, int xTo, int yTo);
    void execute (state::State& state);
    CommandTypeId getCommandTypeId () const;
    // Setters and Getters
    int getXFrom() const;
    void setXFrom(int xFrom);
    int getYFrom() const;
    void setYFrom(int yFrom);
    int getXTo() const;
    void setXTo(int xTo);
    int getYTo() const;
    void setYTo(int yTo);
  };

};

#endif
