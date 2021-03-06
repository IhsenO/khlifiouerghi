// Generated by dia2code
#ifndef STATE__ELEMENT__H
#define STATE__ELEMENT__H


#include "TypeID.h"

namespace state {

  /// class Element - 
  class Element {
    // Associations
    // Attributes
  protected:
    int idPlayer     = -1;
    bool hasPlayed;
    // Operations
  public:
    Element ();
    virtual ~Element ();
    virtual TypeID getTypeID () const = 0;
    virtual bool isInteractive () const = 0;
    virtual bool isStatic () const = 0;
    // Setters and Getters
    int getIdPlayer() const;
    void setIdPlayer(int idPlayer);
    bool getHasPlayed() const;
    void setHasPlayed(bool hasPlayed);
  };

};

#endif
