// Generated by dia2code
#ifndef SERVER__GAME__H
#define SERVER__GAME__H

#include <vector>

namespace server {
  class Player;
}

#include "Player.h"

namespace server {

  /// class Game - 
  class Game {
    // Associations
    // Attributes
  protected:
    std::vector<Player*> players;
    // Operations
  public:
    Game ();
    Player* player (int i);
    int addPlayer (Player* player);
    void removePlayer (int id);
    bool isFullOfPlayers ();
    // Setters and Getters
    const std::vector<Player*>& getPlayers() const;
    void setPlayers(const std::vector<Player*>& players);
  };

};

#endif
