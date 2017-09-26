// Generated by dia2code
#ifndef STATE__LANDSCAPE__H
#define STATE__LANDSCAPE__H


namespace state {
  class Element;
  class StaticElement;
}

#include "TypeID.h"
#include "StaticElement.h"

namespace state {

  /// class Landscape - 
  class Landscape : public state::StaticElement {
    // Attributes
  protected:
    int type;
    // Operations
  public:
    bool const isAccessible ();
    TypeID getTypeID ();
    //bool const equals (const Element& other);
    Landscape ();
    // Setters and Getters
    int getType() const;
    void setType(int type);
  };

};

#endif