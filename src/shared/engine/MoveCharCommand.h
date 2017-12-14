// Generated by dia2code
#ifndef ENGINE__MOVECHARCOMMAND__H
#define ENGINE__MOVECHARCOMMAND__H

#include <stack>
#include <json/json.h>

namespace state {
  class State;
};
namespace engine {
  class Action;
  class MoveCharCommand;
  class Command;
}

#include "CommandTypeId.h"
#include "Command.h"

namespace engine {

  /// class MoveCharCommand - 
  class MoveCharCommand : public engine::Command {
    // Attributes
  protected:
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
    // Operations
  public:
    CommandTypeId getCommandTypeId () const;
    void execute (state::State& state, std::stack<Action*>& actionStack);
    MoveCharCommand (int xFrom, int yFrom, int xTo, int yTo);
    void serialize (Json::Value& out) const;
    MoveCharCommand* deserialize (const Json::Value& in);
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
