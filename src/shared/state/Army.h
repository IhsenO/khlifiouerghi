// Generated by dia2code
#ifndef STATE__ARMY__H
#define STATE__ARMY__H


namespace state {
  class MobileElement;
}

#include "TypeID.h"
#include "MobileElement.h"

namespace state {

  /// class Army - 
  class Army : public state::MobileElement {
    // Attributes
  protected:
    int soldiers;
    // Operations
  public:
    Army ();
    Army (int soldiers, int player);
    TypeID getTypeID () const;
    bool  isMoving () const;
    bool isInteractive () const;
    bool isInCity () const;
    bool isStatic () const;
    // Setters and Getters
    int getSoldiers() const;
    void setSoldiers(int soldiers);
  };

};

#endif
