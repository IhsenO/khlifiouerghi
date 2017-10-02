// Generated by dia2code
#ifndef STATE__CITY__H
#define STATE__CITY__H


namespace state {
  class StaticElement;
  class Construction;
}

#include "TypeID.h"
#include "StaticElement.h"
#include "Construction.h"

namespace state {

  /// class City - 
  class City : public state::StaticElement {
    // Associations
    // Attributes
  protected:
    int defense;
    int listAjouter;
    // Operations
  public:
    City ();
    TypeID getTypeID () const;
    bool isFree () const;
    bool isBuilding () const;
    bool isAccessible () const;
    bool isInteractive () const;
    bool isStatic () const;
    // Setters and Getters
    int getDefense() const;
    void setDefense(int defense);
    int getListAjouter() const;
    void setListAjouter(int listAjouter);
  };

};

#endif
