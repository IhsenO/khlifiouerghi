// Generated by dia2code
#ifndef STATE__MOBILEELEMENT__H
#define STATE__MOBILEELEMENT__H


namespace state {
  class Element;
}

#include "Element.h"

namespace state {

  /// class MobileElement - 
  class MobileElement : public state::Element {
    // Attributes
  public:
    int range;
    // Operations
  public:
    //bool const equals (const Element& other);
    virtual bool const isMoving () = 0;
    // Setters and Getters
  };

};

#endif
