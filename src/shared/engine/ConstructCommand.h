// Generated by dia2code
#ifndef ENGINE__CONSTRUCTCOMMAND__H
#define ENGINE__CONSTRUCTCOMMAND__H

#include <stack>
#include <json/json.h>

namespace engine {
  class Action;
  class ConstructCommand;
  class Command;
};
namespace state {
  class City;
}

#include "CommandTypeId.h"
#include "Command.h"
#include "state/City.h"

namespace engine {

  /// class ConstructCommand - 
  class ConstructCommand : public engine::Command {
    // Attributes
  protected:
    int x;
    int y;
    state::Construction* construction;
    // Operations
  public:
    ConstructCommand (int x, int y, state::Construction* construction);
    CommandTypeId getCommandTypeId () const;
    void execute ( state::State& state, std::stack<Action*>& actionStack);
    void serialize (Json::Value& out) const;
    ConstructCommand* deserialize (const Json::Value& in);
    // Setters and Getters
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    const state::Construction*& getConstruction() const;
    void setConstruction(const state::Construction*& construction);
  };

};

#endif
