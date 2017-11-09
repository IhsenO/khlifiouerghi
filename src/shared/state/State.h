// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H

#include <vector>

namespace state {
  class Player;
  class Monde;
}

#include "Player.h"
#include "Monde.h"

namespace state {

  /// class State - 
  class State {
    // Associations
    // Attributes
  protected:
    std::vector<Player*> players;
    Monde& monde;
    int nbTurns;
    int idPlayer;
    // Operations
  public:
    State (Monde& monde);
    void addPlayer (Player* player);
    Player* getPlayer (int idPlayer) const;
    ~State ();
    // Setters and Getters
    const std::vector<Player*>& getPlayers() const;
    void setPlayers(const std::vector<Player*>& players);
    Monde& getMonde() const;
    void setMonde(const Monde&& monde);
    int getNbTurns() const;
    void setNbTurns(int nbTurns);
    int getIdPlayer() const;
    void setIdPlayer(int idPlayer);
  };

};

#endif
