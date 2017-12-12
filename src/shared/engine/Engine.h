// Generated by dia2code
#ifndef ENGINE__ENGINE__H
#define ENGINE__ENGINE__H

#include <vector>
#include <mutex>
#include <stack>

namespace state {
  class State;
};
namespace engine {
  class Command;
  class Action;
};
namespace ai {
  class AI;
}

#include "ai/AI.h"
#include "Command.h"

namespace engine {

  /// class Engine - 
  class Engine {
    // Associations
    // Attributes
  private:
    state::State& currentState;
    std::vector<Command*> currentCommands;
  protected:
    int player     = 0;
    std::mutex mutexFlag;
    // Operations
  public:
    Engine (state::State& state);
    ~Engine ();
    void addCommand (Command* command);
    void addPassiveCommand ();
    void Update ();
    void runCommand (Command* command, std::stack<Action*>& actionStack);
    const state::State& getState () const;
    void undo (std::stack<Action*>& actionStack);
    void runThread (ai::AI* aiPlayer1, ai::AI* aiPlayer2);
    // Setters and Getters
    int getPlayer() const;
    void setPlayer(int player);
    const std::mutex& getMutexFlag() const;
    void setMutexFlag(const std::mutex& mutexFlag);
  };

};

#endif
