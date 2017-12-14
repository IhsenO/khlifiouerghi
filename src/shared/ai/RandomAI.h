// Generated by dia2code
#ifndef AI__RANDOMAI__H
#define AI__RANDOMAI__H

#include <stack>

namespace state {
  class State;
};
namespace engine {
  class Engine;
  class Action;
};
namespace ai {
  class AI;
}

#include "AI.h"

namespace ai {

  /// class RandomAI - 
  class RandomAI : public ai::AI {
    // Operations
  public:
    RandomAI (state::State& state, engine::Engine& engine);
    void run (engine::Engine& engine, std::stack<engine::Action*>& actionStack, bool serialize);
    // Setters and Getters
  };

};

#endif
