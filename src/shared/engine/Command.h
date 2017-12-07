// Generated by dia2code
#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H

#include <stack>

namespace state {
  class State;
};
namespace engine {
  class Action;
};
namespace state {
  class Element;
}

#include "CommandTypeId.h"
#include "Action.h"
#include "state/Element.h"
#include "state/State.h"

namespace engine {

  /// class Command - 
  class Command {
    // Operations
  public:
    virtual ~Command ();
    virtual CommandTypeId getCommandTypeId () const = 0;
    virtual void execute (state::State& state, std::stack<Action*>& actionStack) = 0;
    // Setters and Getters
  };

};

#endif
