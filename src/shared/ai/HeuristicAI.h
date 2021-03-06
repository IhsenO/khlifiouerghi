// Generated by dia2code
#ifndef AI__HEURISTICAI__H
#define AI__HEURISTICAI__H

#include <stack>

namespace ai {
  class DistanceMap;
};
namespace state {
  class State;
};
namespace engine {
  class Engine;
  class Action;
};
namespace ai {
  class AI;
  class CommandsWeights;
}

#include "DistanceMap.h"
#include "AI.h"
#include "CommandsWeights.h"

namespace ai {

  /// class HeuristicAI - 
  class HeuristicAI : public ai::AI {
    // Associations
    // Attributes
  protected:
    DistanceMap map;
    // Operations
  public:
    HeuristicAI (state::State& state, engine::Engine& engine);
    void run (engine::Engine& engine, std::stack<engine::Action*>& actionStack, bool serialize);
    // Setters and Getters
    const DistanceMap& getMap() const;
    void setMap(const DistanceMap& map);
  };

};

#endif
